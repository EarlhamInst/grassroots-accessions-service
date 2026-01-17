/*
 * pedigree.c
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */



#include "pedigree.h"


PedigreeParent *AllocatePedigreeParent (const char * const store_code_s, const char * const synonym_1_s,
																				const char * const synonym_2_s, const char * const synonym_3_s)
{
	char *copied_store_code_s = EasyCopyToNewString (store_code_s);

	if (copied_store_code_s)
		{
			char *copied_synonym_1_s = EasyCopyToNewString (synonym_1_s);

			if (synonym_1_s)
				{
					char *copied_syn_1_s = NULL;

					if ((syn_1_s == NULL) || ((copied_syn_1_s = EasyCopyToNewString (syn_1_s)) != NULL))
						{
							char *copied_syn_2_s = NULL;

							if ((syn_2_s == NULL) || ((copied_syn_2_s = EasyCopyToNewString (syn_2_s)) != NULL))
								{
									PedigreeParent *ped_par_p = (PedigreeParent *) AllocMemory (sizeof (PedigreeParent));

									if (ped_par_p)
										{
											ped_par_p -> pp_nam_store_code_s = copied_synonym_1_s;
											atk_p -> atr_store_code_s = copied_store_code_s;
											atk_p -> atr_synonym_1_s = copied_syn_1_s;
											atk_p -> atr_synonym_2_s = copied_syn_2_s;

											return ped_par_p;
										}		/* if (atk_p) */
									else
										{
											PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate memory for PedigreeParent (\"%s\", \"%s\"", store_code_s, accession_s);
										}

								}		/* if ((syn_2_s == NULL) || ((copied_syn_2_s = EasyCopyToNewString (syn_2_s)) != NULL)) */
							else
								{

								}

						}		/* if ((syn_1_s == NULL) || ((copied_syn_1_s = EasyCopyToNewString (syn_1_s)) != NULL)) */
					else
						{

						}

					FreeCopiedString (copied_accession_s);
				}		/* if (copied_accession_s) */
			else
				{
					PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to copy accession \"s\"", accession_s);
				}

			FreeCopiedString (copied_store_code_s);
		}		/* if (copied_store_code_s) */
	else
		{
			PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to copy store code \"s\"", store_code_s);
		}

	return NULL;

}


void FreePedigreeParent (PedigreeParent *parent_p)
{
	if (parent_p -> pp_nam_store_code_s)
		{
			FreeCopiedString (parent_p -> pp_nam_store_code_s);
		}

	if (parent_p -> pp_nam_synonym_1_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_1_s);
		}

	if (parent_p -> pp_nam_synonym_2_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_2_s);
		}

	if (parent_p -> pp_nam_synonym_3_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_3_s);
		}

	FreeMemory (parent_p);
}



int CreatePedigreeParentRecordFromTabularJSON (const json_t * const json_p, PedigreeParent **pedgigree_parent_pp)
{
	int res = 0;
	const char * const ATK_STORE_CODE_KEY_S = "ATK_StoreCode";
	const char *store_code_s = GetJSONString (json_p, ATK_STORE_CODE_KEY_S);

	if (!IsStringEmpty (store_code_s))
		{
			const char * const ATK_ACCESSION_KEY_S = "ATK_AccessionName";
			const char *accession_s = GetJSONString (json_p, ATK_ACCESSION_KEY_S);

			if (!IsStringEmpty (accession_s))
				{
					const char * const ATK_SYNONYM_1_KEY_S = "ATK_Synonym1";
					const char * const ATK_SYNONYM_2_KEY_S = "ATK_Synonym2";
					const char *syn_1_s = GetJSONString (json_p, ATK_SYNONYM_1_KEY_S);
					const char *syn_2_s = GetJSONString (json_p, ATK_SYNONYM_2_KEY_S);

					AcademicToolkitRecord *atk_p = AllocateAcademicToolkitRecord (store_code_s, accession_s, syn_1_s, syn_2_s);

					if (atk_p)
						{
							*atk_pp = atk_p;
							res = 1;
						}
					else
						{
							res = -1;
						}

				}		/* if (!IsStringEmpty (accession_s)) */

		}		/* if (!IsStringEmpty (store_code_s)) */

	return res;
}

#include "allergies.h"

#include <stddef.h>

bool is_allergic_to(allergen_t allergen, uint8_t allergy_score)
{
    return (allergy_score & 1 << (int)allergen);
}

allergen_list_t get_allergens(uint16_t allergy_score)
{
    allergen_list_t list = {0};

    for (size_t i = 0; i < ALLERGEN_COUNT; i++)
    {
        if ((allergy_score & 1 << i) != 0)
        {
            list.allergens[i] = true;
            list.count++;
        }
    }

    return list;
}

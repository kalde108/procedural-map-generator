#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "env.h"
extern "C" {
	#include "mlx.h"
}

int init_biome_rules(t_env *env);

int main(int argc, char **argv)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (check_arguments(argc, argv))
		return (1);
	srand(time(NULL));
	if (init_env(&env))
	{
		destroy_env(&env);
		return (1);
	}
	init_biome_rules(&env);
	if (open_mlx_window(&env))
	{
		destroy_env(&env);
		return (1);
	}
	mlx_mouse_get_pos(env.mlx, env.win, &env.input.mouse.x, &env.input.mouse.y);
	mlx_loop(env.mlx);
	
	destroy_env(&env);
	return (0);
}

int init_biome_rules(t_env *env) {
	//                                                              E- E+ T- T+ H- H+ W
	env->biome_rules.push_back({PV_VALLEYS, CONT_COAST, CONT_COAST, 0, 6, 0, 0, 0, 4, VARIANT_NONE, BIOME_FROZEN_RIVER});
	env->biome_rules.push_back({PV_VALLEYS, CONT_COAST, CONT_COAST, 0, 6, 1, 4, 0, 4, VARIANT_NONE, BIOME_RIVER});
	
	env->biome_rules.push_back({PV_VALLEYS, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 5, 0, 0, 0, 4, VARIANT_NONE, BIOME_FROZEN_RIVER});
	env->biome_rules.push_back({PV_VALLEYS, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 5, 1, 4, 0, 4, VARIANT_NONE, BIOME_RIVER});
	
	env->biome_rules.push_back({PV_VALLEYS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 1, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_VALLEYS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_VALLEYS, CONT_MID_INLAND, CONT_FAR_INLAND, 2, 5, 0, 0, 0, 4, VARIANT_NONE, BIOME_FROZEN_RIVER});
	env->biome_rules.push_back({PV_VALLEYS, CONT_MID_INLAND, CONT_FAR_INLAND, 2, 5, 1, 4, 0, 4, VARIANT_NONE, BIOME_RIVER});
	
	env->biome_rules.push_back({PV_VALLEYS, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 0, 0, 0, 4, VARIANT_NONE, BIOME_FROZEN_RIVER});
	env->biome_rules.push_back({PV_VALLEYS, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 1, 2, 0, 4, VARIANT_NONE, BIOME_SWAMP});
	env->biome_rules.push_back({PV_VALLEYS, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 3, 4, 0, 4, VARIANT_NONE, BIOME_MANGROVE_SWAMP});
	
	
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 0, 2, 0, 4, 0, 4, VARIANT_NONE, BIOME_STONY_SHORE});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 3, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BEACH});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_BEACH});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 5, 5, 0, 1, 0, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 5, 5, 0, 4, 4, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});
	env->biome_rules.push_back({PV_LOW, CONT_COAST, CONT_COAST, 6, 6, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BEACH});

	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 1, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 2, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 1, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 4, 4, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});

	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 0, 0, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 0, 0, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 1, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 2, 3, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 2, 3, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_LOW, CONT_MID_INLAND, CONT_FAR_INLAND, 4, 5, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});

	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 0, 0, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 1, 2, 0, 4, VARIANT_NONE, BIOME_SWAMP});
	env->biome_rules.push_back({PV_LOW, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 3, 4, 0, 4, VARIANT_NONE, BIOME_MANGROVE_SWAMP});


	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 0, 2, 0, 4, 0, 4, VARIANT_NONE, BIOME_STONY_SHORE});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 3, 3, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 4, 4, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_BEACH});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 4, 4, 0, 4, 0, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_BEACH});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 5, 5, 0, 1, 0, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 5, 5, 0, 4, 4, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 6, 6, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_BEACH});
	env->biome_rules.push_back({PV_MID, CONT_COAST, CONT_COAST, 6, 6, 0, 4, 0, 4, VARIANT_VARIANT, BIOME_TYPE_MIDDLE});

	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 0, 0, 0, 2, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 0, 0, 0, 2, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 0, 0, 3, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});

	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_MID_INLAND, 1, 1, 0, 0, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_MID_INLAND, 1, 1, 0, 0, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_MID_INLAND, 1, 1, 1, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_MID_INLAND, 1, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 2, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 1, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 0, 4, 4, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});

	env->biome_rules.push_back({PV_MID, CONT_MID_INLAND, CONT_MID_INLAND, 2, 3, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_MID_INLAND, CONT_MID_INLAND, 2, 3, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 1, 1, 0, 0, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 1, 1, 0, 0, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 1, 1, 1, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});
	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 2, 2, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});
	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 3, 3, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_FAR_INLAND, CONT_FAR_INLAND, 3, 3, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_MID, CONT_MID_INLAND, CONT_FAR_INLAND, 4, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_MID_INLAND, CONT_FAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_SHATTERED});

	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 0, 0, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 1, 2, 0, 4, VARIANT_NONE, BIOME_SWAMP});
	env->biome_rules.push_back({PV_MID, CONT_NEAR_INLAND, CONT_FAR_INLAND, 6, 6, 3, 4, 0, 4, VARIANT_NONE, BIOME_MANGROVE_SWAMP});


	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_COAST, 0, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});

	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 0, 0, 2, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 0, 0, 2, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 0, 0, 3, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 1, 1, 0, 0, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 1, 1, 0, 0, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 1, 1, 2, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 1, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_HIGH, CONT_NEAR_INLAND, CONT_NEAR_INLAND, 2, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});

	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 1, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 4, 4, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});

	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 0, 0, 2, 0, 4, VARIANT_BASE, BIOME_JAGGED_PEAKS});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 0, 0, 2, 0, 4, VARIANT_VARIANT, BIOME_FROZEN_PEAKS});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 0, 3, 3, 0, 4, VARIANT_NONE, BIOME_STONY_PEAKS});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 0, 4, 4, 0, 4, VARIANT_NONE, BIOME_BADLANDS});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 1, 1, 0, 2, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 1, 1, 0, 2, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 1, 1, 3, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});

	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_MID_INLAND, 2, 2, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_MID_INLAND, 3, 3, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_MID_INLAND, 3, 3, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_HIGH, CONT_FAR_INLAND, CONT_FAR_INLAND, 2, 3, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});

	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 4, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_HIGH, CONT_MID_INLAND, CONT_FAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_SHATTERED});

	env->biome_rules.push_back({PV_HIGH, CONT_COAST, CONT_FAR_INLAND, 6, 6, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});


	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 0, 0, 0, 2, 0, 4, VARIANT_BASE, BIOME_JAGGED_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 0, 0, 0, 2, 0, 4, VARIANT_VARIANT, BIOME_FROZEN_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 0, 0, 3, 3, 0, 4, VARIANT_NONE, BIOME_STONY_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 0, 0, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 1, 1, 0, 0, 0, 1, VARIANT_NONE, BIOME_SNOWY_SLOPES});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 1, 1, 0, 0, 2, 4, VARIANT_NONE, BIOME_GROVE});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 1, 1, 1, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 1, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 2, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_BASE, BIOME_TYPE_SHATTERED});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 1, 0, 4, VARIANT_NONE, BIOME_TYPE_SHATTERED});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 0, 4, 4, 4, VARIANT_NONE, BIOME_TYPE_SHATTERED});
	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_NEAR_INLAND, 5, 5, 2, 4, 0, 3, VARIANT_VARIANT, BIOME_WINDSWEPT_SAVANNA});

	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 0, 2, 0, 4, VARIANT_BASE, BIOME_JAGGED_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 0, 2, 0, 4, VARIANT_VARIANT, BIOME_FROZEN_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 3, 3, 0, 4, VARIANT_NONE, BIOME_STONY_PEAKS});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 0, 1, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_MID_INLAND, 2, 2, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_MID_INLAND, 3, 3, 0, 3, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_MID_INLAND, 3, 3, 4, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_BADLAND});

	env->biome_rules.push_back({PV_PEAKS, CONT_FAR_INLAND, CONT_FAR_INLAND, 2, 3, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_PLATEAU});

	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 4, 4, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});
	env->biome_rules.push_back({PV_PEAKS, CONT_MID_INLAND, CONT_FAR_INLAND, 5, 5, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_SHATTERED});

	env->biome_rules.push_back({PV_PEAKS, CONT_COAST, CONT_FAR_INLAND, 6, 6, 0, 4, 0, 4, VARIANT_NONE, BIOME_TYPE_MIDDLE});

	return 0;
}

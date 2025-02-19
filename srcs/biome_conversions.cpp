#include "map.h"
#include <stddef.h>

Continentalness_t noise_to_continentalness(double noise) {
	if (noise < CONT_MUSHROOM_FIELDS_THRESHOLD) {
		return CONT_MUSHROOM_FIELDS;
	} else if (noise < CONT_DEEP_OCEAN_THRESHOLD) {
		return CONT_DEEP_OCEAN;
	} else if (noise < CONT_OCEAN_THRESHOLD) {
		return CONT_OCEAN;
	} else if (noise < CONT_COAST_THRESHOLD) {
		return CONT_COAST;
	} else if (noise < CONT_NEAR_INLAND_THRESHOLD) {
		return CONT_NEAR_INLAND;
	} else if (noise < CONT_MID_INLAND_THRESHOLD) {
		return CONT_MID_INLAND;
	} else {
		return CONT_FAR_INLAND;
	}
}

PeaksValleys_t noise_to_pv(double noise) {
	if (noise < PV_VALLEYS_THRESHOLD) {
		return PV_VALLEYS;
	} else if (noise < PV_LOW_THRESHOLD) {
		return PV_LOW;
	} else if (noise < PV_MID_THRESHOLD) {
		return PV_MID;
	} else if (noise < PV_HIGH_THRESHOLD) {
		return PV_HIGH;
	} else {
		return PV_PEAKS;
	}
}

int noise_to_temperature_level(double noise) {
	if (noise < TEMP_LEVEL_0_THRESHOLD) {
		return 0;
	} else if (noise < TEMP_LEVEL_1_THRESHOLD) {
		return 1;
	} else if (noise < TEMP_LEVEL_2_THRESHOLD) {
		return 2;
	} else if (noise < TEMP_LEVEL_3_THRESHOLD) {
		return 3;
	} else {
		return 4;
	}
}

int noise_to_humidity_level(double noise) {
	if (noise < HUM_LEVEL_0_THRESHOLD) {
		return 0;
	} else if (noise < HUM_LEVEL_1_THRESHOLD) {
		return 1;
	} else if (noise < HUM_LEVEL_2_THRESHOLD) {
		return 2;
	} else if (noise < HUM_LEVEL_3_THRESHOLD) {
		return 3;
	} else {
		return 4;
	}
}

int noise_to_erosion_level(double noise) {
	if (noise < ERO_LEVEL_0_THRESHOLD) {
		return 0;
	} else if (noise < ERO_LEVEL_1_THRESHOLD) {
		return 1;
	} else if (noise < ERO_LEVEL_2_THRESHOLD) {
		return 2;
	} else if (noise < ERO_LEVEL_3_THRESHOLD) {
		return 3;
	} else if (noise < ERO_LEVEL_4_THRESHOLD) {
		return 4;
	} else if (noise < ERO_LEVEL_5_THRESHOLD) {
		return 5;
	} else {
		return 6;
	}
}

Biome_t deep_ocean_to_biome(int temperature_level) {
	if (temperature_level == 0) {
		return BIOME_DEEP_FROZEN_OCEAN;
	} else if (temperature_level == 1) {
		return BIOME_DEEP_COLD_OCEAN;
	} else if (temperature_level == 2) {
		return BIOME_DEEP_OCEAN;
	} else if (temperature_level == 3) {
		return BIOME_DEEP_LUKEWARM_OCEAN;
	} else if (temperature_level == 4) {
		return BIOME_WARM_OCEAN;
	} else {
		return BIOME_COUNT;
	}
}

Biome_t ocean_to_biome(int temperature_level) {
	if (temperature_level == 0) {
		return BIOME_FROZEN_OCEAN;
	} else if (temperature_level == 1) {
		return BIOME_COLD_OCEAN;
	} else if (temperature_level == 2) {
		return BIOME_OCEAN;
	} else if (temperature_level == 3) {
		return BIOME_LUKEWARM_OCEAN;
	} else if (temperature_level == 4) {
		return BIOME_WARM_OCEAN;
	} else {
		return BIOME_COUNT;
	}
}

Biome_t beach_type_resolve(int temperature_level) {
	if (temperature_level == 0) {
		return BIOME_SNOWY_BEACH;
	} else if (temperature_level >= 1 && temperature_level <= 3) {
		return BIOME_BEACH;
	} else if (temperature_level == 4) {
		return BIOME_DESERT;
	} else {
		return BIOME_COUNT;
	}
}

Biome_t badland_type_resolve(int humidity_level, double weirdness) {
	if (humidity_level == 0 || humidity_level == 1) {
		if (weirdness <= 0) {
			return BIOME_BADLANDS;
		} else {
			return BIOME_ERODED_BADLANDS;
		}
	} else if (humidity_level == 2) {
		return BIOME_BADLANDS;
	} else if (humidity_level == 3 || humidity_level == 4) {
		return BIOME_WOODED_BADLANDS;
	} else {
		return BIOME_COUNT;
	}
}

Biome_t middle_type_resolve(int temperature_level, int humidity_level, double weirdness) {
	if (temperature_level == 0) {
		if (humidity_level == 0) {
			if (weirdness <= 0) {
				return BIOME_SNOWY_PLAINS;
			} else {
				return BIOME_ICE_SPIKES;
			}
		} else if (humidity_level == 1) {
			return BIOME_SNOWY_PLAINS;
		} else if (humidity_level == 2) {
			if (weirdness <= 0) {
				return BIOME_SNOWY_PLAINS;
			} else {
				return BIOME_SNOWY_TAIGA;
			}
		} else if (humidity_level == 3) {
			return BIOME_SNOWY_TAIGA;
		} else if (humidity_level == 4) {
			return BIOME_TAIGA;
		}
	} else if (temperature_level == 1) {
		if (humidity_level == 0 || humidity_level == 1) {
			return BIOME_PLAINS;
		} else if (humidity_level == 2) {
			return BIOME_FOREST;
		} else if (humidity_level == 3) {
			return BIOME_TAIGA;
		} else if (humidity_level == 4) {
			if (weirdness <= 0) {
				return BIOME_OLD_GROWTH_SPRUCE_TAIGA;
			} else {
				return BIOME_OLD_GROWTH_PINE_TAIGA;
			}
		}
	} else if (temperature_level == 2) {
		if (humidity_level == 0) {
			if (weirdness <= 0) {
				return BIOME_FLOWER_FOREST;
			} else {
				return BIOME_SUNFLOWER_PLAINS;
			}
		} else if (humidity_level == 1) {
			return BIOME_PLAINS;
		} else if (humidity_level == 2) {
			return BIOME_FOREST;
		} else if (humidity_level == 3) {
			if (weirdness <= 0) {
				return BIOME_BIRCH_FOREST;
			} else {
				return BIOME_OLD_GROWTH_BIRCH_FOREST;
			}
		} else if (humidity_level == 4) {
			return BIOME_DARK_FOREST;
		}
	} else if (temperature_level == 3) {
		if (humidity_level == 0 || humidity_level == 1) {
			return BIOME_SAVANNA;
		} else if (humidity_level == 2) {
			if (weirdness <= 0) {
				return BIOME_FOREST;
			} else {
				return BIOME_PLAINS;
			}
		} else if (humidity_level == 3) {
			if (weirdness <= 0) {
				return BIOME_JUNGLE;
			} else {
				return BIOME_SPARSE_JUNGLE;
			}
		} else if (humidity_level == 4) {
			if (weirdness <= 0) {
				return BIOME_JUNGLE;
			} else {
				return BIOME_BAMBOO_JUNGLE;
			}
		}
	} else if (temperature_level == 4) {
		return BIOME_DESERT;
	}
	return BIOME_COUNT;
}

Biome_t plateau_type_resolve(int temperature_level, int humidity_level, double weirdness) {
	if (temperature_level == 0) {
		if (humidity_level == 0) {
			if (weirdness <= 0) {
				return BIOME_SNOWY_PLAINS;
			} else {
				return BIOME_ICE_SPIKES;
			}
		} else if (humidity_level == 1 || humidity_level == 2) {
			return BIOME_SNOWY_PLAINS;
		} else if (humidity_level == 3 || humidity_level == 4) {
			return BIOME_SNOWY_TAIGA;
		}
	} else if (temperature_level == 1) {
		if (humidity_level == 0) {
			if (weirdness <= 0) {
				return BIOME_MEADOW;
			} else {
				return BIOME_CHERRY_GROVE;
			}
		} else if (humidity_level == 1) {
			return BIOME_MEADOW;
		} else if (humidity_level == 2) {
			if (weirdness <= 0) {
				return BIOME_FOREST;
			} else {
				return BIOME_MEADOW;
			}
		} else if (humidity_level == 3) {
			if (weirdness <= 0) {
				return BIOME_TAIGA;
			} else {
				return BIOME_MEADOW;
			}
		} else if (humidity_level == 4) {
			if (weirdness <= 0) {
				return BIOME_OLD_GROWTH_SPRUCE_TAIGA;
			} else {
				return BIOME_OLD_GROWTH_PINE_TAIGA;
			}
		}
	} else if (temperature_level == 2) {
		if (humidity_level == 0 || humidity_level == 1) {
			if (weirdness <= 0) {
				return BIOME_MEADOW;
			} else {
				return BIOME_CHERRY_GROVE;
			}
		} else if (humidity_level == 2) {
			if (weirdness <= 0) {
				return BIOME_MEADOW;
			} else {
				return BIOME_FOREST;
			}
		} else if (humidity_level == 3) {
			if (weirdness <= 0) {
				return BIOME_MEADOW;
			} else {
				return BIOME_BIRCH_FOREST;
			}
		} else if (humidity_level == 4) {
			if (weirdness <= 0) {
				return BIOME_DARK_FOREST;
			} else {
				return BIOME_PALE_GARDEN;
			}
		}
	} else if (temperature_level == 3) {
		if (humidity_level == 0 || humidity_level == 1) {
			return BIOME_SAVANNA_PLATEAU;
		} else if (humidity_level == 2 || humidity_level == 3) {
			return BIOME_FOREST;
		} else if (humidity_level == 4) {
			return BIOME_JUNGLE;
		}
	} else if (temperature_level == 4) {
		if (humidity_level == 0 && humidity_level == 1) {
			if (weirdness <= 0) {
				return BIOME_BADLANDS;
			} else {
				return BIOME_ERODED_BADLANDS;
			}
		} else if (humidity_level == 2) {
			return BIOME_BADLANDS;
		} else if (humidity_level == 3 || humidity_level == 4) {
			return BIOME_WOODED_BADLANDS;
		}
	}
	return BIOME_COUNT;
}

Biome_t shattered_type_resolve(int temperature_level, int humidity_level, double weirdness) {
	if (temperature_level == 0 || temperature_level == 1) {
		if (humidity_level == 0 || humidity_level == 1) {
			return BIOME_WINDSWEPT_GRAVELLY_HILLS;
		} else if (humidity_level == 2) {
			return BIOME_WINDSWEPT_HILLS;
		} else if (humidity_level == 3 || humidity_level == 4) {
			return BIOME_WINDSWEPT_FOREST;
		}
	} else if (temperature_level == 2) {
		if (humidity_level >= 0 && humidity_level <= 2) {
			return BIOME_WINDSWEPT_HILLS;
		} else if (humidity_level == 3 || humidity_level == 4) {
			return BIOME_WINDSWEPT_FOREST;
		}
	} else if (temperature_level == 3) {
		if (humidity_level == 0 || humidity_level == 1) {
			return BIOME_SAVANNA;
		} else if (humidity_level == 2) {
			if (weirdness <= 0) {
				return BIOME_FOREST;
			} else {
				return BIOME_PLAINS;
			}
		} else if (humidity_level == 3) {
			if (weirdness <= 0) {
				return BIOME_JUNGLE;
			} else {
				return BIOME_SPARSE_JUNGLE;
			}
		} else if (humidity_level == 4) {
			if (weirdness <= 0) {
				return BIOME_JUNGLE;
			} else {
				return BIOME_BAMBOO_JUNGLE;
			}
		}
	} else if (temperature_level == 4) {
		return BIOME_DESERT;
	}
	return BIOME_COUNT;
}

Biome_t lookupBiome(std::vector<BiomeRule_t> &biome_rules, int pv, int erosion, int continentalness, int temperature, int humidity, bool weirdness) {
    for (size_t i = 0; i < biome_rules.size(); i++) {
        BiomeRule_t &rule = biome_rules[i];
        if (pv = rule.pv &&
			erosion >= rule.erosion_min && erosion <= rule.erosion_max &&
			continentalness >= rule.continentalness_min && continentalness <= rule.continentalness_max &&
			temperature >= rule.temp_min && temperature <= rule.temp_max &&
			humidity >= rule.humidity_min && humidity <= rule.humidity_max &&
			(rule.variant == VARIANT_NONE || (rule.variant == 0 && !weirdness) || (rule.variant == 1 && weirdness)))
        {
            return rule.biome;
        }
    }
    // Fallback case, if nothing matches.
    return BIOME_THE_VOID;
}

t_color biome_color(Biome_t biome) {
	static const t_color biome_colors[] = {
		BIOME_COLOR_THE_VOID,
		BIOME_COLOR_OCEAN,
		BIOME_COLOR_DEEP_OCEAN,
		BIOME_COLOR_WARM_OCEAN,
		BIOME_COLOR_LUKEWARM_OCEAN,
		BIOME_COLOR_DEEP_LUKEWARM_OCEAN,
		BIOME_COLOR_COLD_OCEAN,
		BIOME_COLOR_DEEP_COLD_OCEAN,
		BIOME_COLOR_FROZEN_OCEAN,
		BIOME_COLOR_DEEP_FROZEN_OCEAN,
		BIOME_COLOR_MUSHROOM_FIELDS,
		BIOME_COLOR_JAGGED_PEAKS,
		BIOME_COLOR_FROZEN_PEAKS,
		BIOME_COLOR_STONY_PEAKS,
		BIOME_COLOR_MEADOW,
		BIOME_COLOR_CHERRY_GROVE,
		BIOME_COLOR_GROVE,
		BIOME_COLOR_SNOWY_SLOPES,
		BIOME_COLOR_WINDSWEPT_HILLS,
		BIOME_COLOR_WINDSWEPT_GRAVELLY_HILLS,
		BIOME_COLOR_WINDSWEPT_FOREST,
		BIOME_COLOR_FOREST,
		BIOME_COLOR_FLOWER_FOREST,
		BIOME_COLOR_TAIGA,
		BIOME_COLOR_OLD_GROWTH_PINE_TAIGA,
		BIOME_COLOR_OLD_GROWTH_SPRUCE_TAIGA,
		BIOME_COLOR_SNOWY_TAIGA,
		BIOME_COLOR_BIRCH_FOREST,
		BIOME_COLOR_OLD_GROWTH_BIRCH_FOREST,
		BIOME_COLOR_DARK_FOREST,
		BIOME_COLOR_PALE_GARDEN,
		BIOME_COLOR_JUNGLE,
		BIOME_COLOR_SPARSE_JUNGLE,
		BIOME_COLOR_BAMBOO_JUNGLE,
		BIOME_COLOR_RIVER,
		BIOME_COLOR_FROZEN_RIVER,
		BIOME_COLOR_SWAMP,
		BIOME_COLOR_MANGROVE_SWAMP,
		BIOME_COLOR_BEACH,
		BIOME_COLOR_SNOWY_BEACH,
		BIOME_COLOR_STONY_SHORE,
		BIOME_COLOR_PLAINS,
		BIOME_COLOR_SUNFLOWER_PLAINS,
		BIOME_COLOR_SNOWY_PLAINS,
		BIOME_COLOR_ICE_SPIKES,
		BIOME_COLOR_DESERT,
		BIOME_COLOR_SAVANNA,
		BIOME_COLOR_SAVANNA_PLATEAU,
		BIOME_COLOR_WINDSWEPT_SAVANNA,
		BIOME_COLOR_BADLANDS,
		BIOME_COLOR_WOODED_BADLANDS,
		BIOME_COLOR_ERODED_BADLANDS,
		BIOME_COLOR_DEEP_DARK,
		BIOME_COLOR_DRIPSTONE_CAVES,
		BIOME_COLOR_LUSH_CAVES
	};

	if (biome > BIOME_COUNT) {
		return biome_colors[BIOME_THE_VOID];
	}
	return biome_colors[biome];
}

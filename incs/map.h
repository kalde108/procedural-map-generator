#ifndef MAP_H
# define MAP_H

# include <cstdbool>
# include <cstdint>
# include <vector>

typedef enum {
	NOISE_CONTINENTS = 0,
	NOISE_EROSION,
	NOISE_TEMPERATURE,
	NOISE_VEGETATION,
	NOISE_RIDGES,
	NOISE_COUNT
}	NoiseEnum_t;

typedef enum {
	CONT_MUSHROOM_FIELDS,
	CONT_DEEP_OCEAN,
	CONT_OCEAN,
	CONT_COAST,
	CONT_NEAR_INLAND,
	CONT_MID_INLAND,
	CONT_FAR_INLAND
}	Continentalness_t;

# define CONT_MUSHROOM_FIELDS_THRESHOLD -1.05
# define CONT_DEEP_OCEAN_THRESHOLD -0.455
# define CONT_OCEAN_THRESHOLD -0.19
# define CONT_COAST_THRESHOLD -0.11
# define CONT_NEAR_INLAND_THRESHOLD 0.03
# define CONT_MID_INLAND_THRESHOLD 0.3
// # define CONT_FAR_INLAND_THRESHOLD 1.0

typedef enum {
	PV_VALLEYS,
	PV_LOW,
	PV_MID,
	PV_HIGH,
	PV_PEAKS
}	PeaksValleys_t;

# define PV_VALLEYS_THRESHOLD -0.85
# define PV_LOW_THRESHOLD -0.6
# define PV_MID_THRESHOLD 0.2
# define PV_HIGH_THRESHOLD 0.7
// # define PV_PEAKS_THRESHOLD 1.0

typedef enum {
	TEMP_LEVEL_0,
	TEMP_LEVEL_1,
	TEMP_LEVEL_2,
	TEMP_LEVEL_3,
	TEMP_LEVEL_4
}	TemperatureLevel_t;

# define TEMP_LEVEL_0_THRESHOLD -0.45
# define TEMP_LEVEL_1_THRESHOLD -0.15
# define TEMP_LEVEL_2_THRESHOLD 0.2
# define TEMP_LEVEL_3_THRESHOLD 0.55
// # define TEMP_LEVEL_4_THRESHOLD 1.0

typedef enum {
	HUM_LEVEL_0,
	HUM_LEVEL_1,
	HUM_LEVEL_2,
	HUM_LEVEL_3,
	HUM_LEVEL_4
}	HumidityLevel_t;

# define HUM_LEVEL_0_THRESHOLD -0.35
# define HUM_LEVEL_1_THRESHOLD -0.1
# define HUM_LEVEL_2_THRESHOLD 0.1
# define HUM_LEVEL_3_THRESHOLD 0.3
// # define HUM_LEVEL_4_THRESHOLD 1.0

typedef enum {
	ERO_LEVEL_0,
	ERO_LEVEL_1,
	ERO_LEVEL_2,
	ERO_LEVEL_3,
	ERO_LEVEL_4,
	ERO_LEVEL_5,
	ERO_LEVEL_6
}	ErosionLevel_t;

# define ERO_LEVEL_0_THRESHOLD -0.78
# define ERO_LEVEL_1_THRESHOLD -0.375
# define ERO_LEVEL_2_THRESHOLD -0.2225
# define ERO_LEVEL_3_THRESHOLD 0.05
# define ERO_LEVEL_4_THRESHOLD 0.45
# define ERO_LEVEL_5_THRESHOLD 0.55
// # define ERO_LEVEL_6_THRESHOLD 1.0

// # define IS_INLAND_BIOME(cont) ((cont) >= CONT_NEAR_INLAND)

typedef enum {
	BIOME_THE_VOID,
	BIOME_OCEAN,
	BIOME_DEEP_OCEAN,
	BIOME_WARM_OCEAN,
	BIOME_LUKEWARM_OCEAN,
	BIOME_DEEP_LUKEWARM_OCEAN,
	BIOME_COLD_OCEAN,
	BIOME_DEEP_COLD_OCEAN,
	BIOME_FROZEN_OCEAN,
	BIOME_DEEP_FROZEN_OCEAN,
	BIOME_MUSHROOM_FIELDS,
	BIOME_JAGGED_PEAKS,
	BIOME_FROZEN_PEAKS,
	BIOME_STONY_PEAKS,
	BIOME_MEADOW,
	BIOME_CHERRY_GROVE,
	BIOME_GROVE,
	BIOME_SNOWY_SLOPES,
	BIOME_WINDSWEPT_HILLS,
	BIOME_WINDSWEPT_GRAVELLY_HILLS,
	BIOME_WINDSWEPT_FOREST,
	BIOME_FOREST,
	BIOME_FLOWER_FOREST,
	BIOME_TAIGA,
	BIOME_OLD_GROWTH_PINE_TAIGA,
	BIOME_OLD_GROWTH_SPRUCE_TAIGA,
	BIOME_SNOWY_TAIGA,
	BIOME_BIRCH_FOREST,
	BIOME_OLD_GROWTH_BIRCH_FOREST,
	BIOME_DARK_FOREST,
	BIOME_PALE_GARDEN,
	BIOME_JUNGLE,
	BIOME_SPARSE_JUNGLE,
	BIOME_BAMBOO_JUNGLE,
	BIOME_RIVER,
	BIOME_FROZEN_RIVER,
	BIOME_SWAMP,
	BIOME_MANGROVE_SWAMP,
	BIOME_BEACH,
	BIOME_SNOWY_BEACH,
	BIOME_STONY_SHORE,
	BIOME_PLAINS,
	BIOME_SUNFLOWER_PLAINS,
	BIOME_SNOWY_PLAINS,
	BIOME_ICE_SPIKES,
	BIOME_DESERT,
	BIOME_SAVANNA,
	BIOME_SAVANNA_PLATEAU,
	BIOME_WINDSWEPT_SAVANNA,
	BIOME_BADLANDS,
	BIOME_WOODED_BADLANDS,
	BIOME_ERODED_BADLANDS,
	BIOME_DEEP_DARK,
	BIOME_DRIPSTONE_CAVES,
	BIOME_LUSH_CAVES,
	BIOME_COUNT,
	BIOME_TYPE_BEACH,
	BIOME_TYPE_BADLAND,
	BIOME_TYPE_MIDDLE,
	BIOME_TYPE_PLATEAU,
	BIOME_TYPE_SHATTERED
}	Biome_t;

# define VARIANT_NONE -1
# define VARIANT_BASE 0
# define VARIANT_VARIANT 1

typedef struct {
    // Ranges (inclusive) for each dimension; use -1 or similar to indicate “don’t care”
    PeaksValleys_t pv;
    Continentalness_t continentalness_min, continentalness_max;
    uint8_t erosion_min, erosion_max;
    uint8_t temp_min, temp_max;
    uint8_t humidity_min, humidity_max;
    int8_t variant; // if -1, ignore weirdness; if 0, weirdness must be false (<=0); if 1, must be true (>0)
    Biome_t biome;
} BiomeRule_t;

Continentalness_t noise_to_continentalness(double noise);
PeaksValleys_t noise_to_pv(double noise);
int noise_to_temperature_level(double noise);
int noise_to_humidity_level(double noise);
int noise_to_erosion_level(double noise);
Biome_t deep_ocean_to_biome(int temperature_level);
Biome_t ocean_to_biome(int temperature_level);
Biome_t beach_type_resolve(int temperature_level);
Biome_t badland_type_resolve(int humidity_level, double weirdness);
Biome_t middle_type_resolve(int temperature_level, int humidity_level, double weirdness);
Biome_t plateau_type_resolve(int temperature_level, int humidity_level, double weirdness);
Biome_t shattered_type_resolve(int temperature_level, int humidity_level, double weirdness);

Biome_t lookupBiome(std::vector<BiomeRule_t> &biome_rules, int pv, int erosion, int continentalness, int temperature, int humidity, bool weirdness);

#endif


/*

OCEAN
DEEP_OCEAN
WARM_OCEAN
LUKEWARM_OCEAN
DEEP_LUKEWARM_OCEAN
COLD_OCEAN
DEEP_COLD_OCEAN
FROZEN_OCEAN
DEEP_FROZEN_OCEAN
MUSHROOM_FIELDS


JAGGED_PEAKS
FROZEN_PEAKS
STONY_PEAKS
MEADOW
CHERRY_GROVE
GROVE
SNOWY_SLOPES
WINDSWEPT_HILLS
WINDSWEPT_GRAVELLY_HILLS
WINDSWEPT_FOREST


FOREST
FLOWER_FOREST
TAIGA
OLD_GROWTH_PINE_TAIGA
OLD_GROWTH_SPRUCE_TAIGA
SNOWY_TAIGA
BIRCH_FOREST
OLD_GROWTH_BIRCH_FOREST
DARK_FOREST
PALE_GARDEN
JUNGLE
SPARSE_JUNGLE
BAMBOO_JUNGLE


RIVER
FROZEN_RIVER
SWAMP
MANGROVE_SWAMP
BEACH
SNOWY_BEACH
STONY_SHORE


PLAINS
SUNFLOWER_PLAINS
SNOWY_PLAINS
ICE_SPIKES


DESERT
SAVANNA
SAVANNA_PLATEAU
WINDSWEPT_SAVANNA
BADLANDS
WOODED_BADLANDS
ERODED_BADLANDS


DEEP_DARK
DRIPSTONE_CAVES
LUSH_CAVES

*/

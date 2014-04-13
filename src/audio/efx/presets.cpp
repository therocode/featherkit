#include <featherkit/audio/efx/presets.hpp>
#include <AL/efx-presets.h>

namespace fea
{
    static void loadFromEAXPreset(Reverb& reverb, EFXEAXREVERBPROPERTIES& properties)
    {
        reverb.setDensity(properties.flDensity);
        reverb.setDiffusion(properties.flDiffusion);
        reverb.setReverbGain(properties.flGain);
        reverb.setHFGain(properties.flGainHF);
        reverb.setDecayTime(properties.flDecayTime);
        reverb.setDecayHFRatio(properties.flDecayHFRatio);
        reverb.setReflectionsGain(properties.flReflectionsGain);
        reverb.setReflectionsDelay(properties.flReflectionsDelay);
        reverb.setLateGain(properties.flLateReverbGain);
        reverb.setLateDelay(properties.flLateReverbDelay);
        reverb.setRoomRolloffFactor(properties.flRoomRolloffFactor);
        reverb.setAirAbsorptionGainHF(properties.flAirAbsorptionGainHF);
        reverb.setDecayHFLimit(properties.iDecayHFLimit == AL_TRUE ? true : false);
    }

    static void loadReverbPreset(Reverb& reverb, ReverbPreset preset)
    {
        switch(preset)
        {
            EFXEAXREVERBPROPERTIES properties;
            case GENERIC: 
                properties = EFX_REVERB_PRESET_GENERIC;
                loadFromEAXPreset(reverb, properties);
                break;
            case PADDED_CELL: 
                properties = EFX_REVERB_PRESET_PADDEDCELL;
                loadFromEAXPreset(reverb, properties);
                break;
            case ROOM: 
                properties = EFX_REVERB_PRESET_ROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case BATHROOM: 
                properties = EFX_REVERB_PRESET_BATHROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case LIVING_ROOM: 
                properties = EFX_REVERB_PRESET_LIVINGROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case STONE_ROOM: 
                properties = EFX_REVERB_PRESET_STONEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case AUDITORIUM: 
                properties = EFX_REVERB_PRESET_AUDITORIUM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CONCERT_HALL: 
                properties = EFX_REVERB_PRESET_CONCERTHALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case CAVE: 
                properties = EFX_REVERB_PRESET_CAVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case ARENA: 
                properties = EFX_REVERB_PRESET_ARENA;
                loadFromEAXPreset(reverb, properties);
                break;
            case HANGAR: 
                properties = EFX_REVERB_PRESET_HANGAR;
                loadFromEAXPreset(reverb, properties);
                break;
            case CARPETED_HALLWAY: 
                properties = EFX_REVERB_PRESET_CARPETEDHALLWAY;
                loadFromEAXPreset(reverb, properties);
                break;
            case HALLWAY: 
                properties = EFX_REVERB_PRESET_HALLWAY;
                loadFromEAXPreset(reverb, properties);
                break;
            case STONE_CORRIDOR: 
                properties = EFX_REVERB_PRESET_STONECORRIDOR;
                loadFromEAXPreset(reverb, properties);
                break;
            case ALLEY: 
                properties = EFX_REVERB_PRESET_ALLEY;
                loadFromEAXPreset(reverb, properties);
                break;
            case FOREST: 
                properties = EFX_REVERB_PRESET_FOREST;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY: 
                properties = EFX_REVERB_PRESET_CITY;
                loadFromEAXPreset(reverb, properties);
                break;
            case MOUNTAINS: 
                properties = EFX_REVERB_PRESET_MOUNTAINS;
                loadFromEAXPreset(reverb, properties);
                break;
            case QUARRY: 
                properties = EFX_REVERB_PRESET_QUARRY;
                loadFromEAXPreset(reverb, properties);
                break;
            case PLAIN: 
                properties = EFX_REVERB_PRESET_PLAIN;
                loadFromEAXPreset(reverb, properties);
                break;
            case PARKING_LOT: 
                properties = EFX_REVERB_PRESET_PARKINGLOT;
                loadFromEAXPreset(reverb, properties);
                break;
            case SEWER_PIPE: 
                properties = EFX_REVERB_PRESET_SEWERPIPE;
                loadFromEAXPreset(reverb, properties);
                break;
            case UNDER_WATER: 
                properties = EFX_REVERB_PRESET_UNDERWATER;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRUGGED: 
                properties = EFX_REVERB_PRESET_DRUGGED;
                loadFromEAXPreset(reverb, properties);
                break;
            case DIZZY: 
                properties = EFX_REVERB_PRESET_DIZZY;
                loadFromEAXPreset(reverb, properties);
                break;
            case PSYCHOTIC: 
                properties = EFX_REVERB_PRESET_PSYCHOTIC;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_SMALL_ROOM: 
                properties = EFX_REVERB_PRESET_CASTLE_SMALLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_SHORT_PASSAGE: 
                properties = EFX_REVERB_PRESET_CASTLE_SHORTPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_MEDIUM_ROOM: 
                properties = EFX_REVERB_PRESET_CASTLE_MEDIUMROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_LARGE_ROOM: 
                properties = EFX_REVERB_PRESET_CASTLE_LARGEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_LONG_PASSAGE: 
                properties = EFX_REVERB_PRESET_CASTLE_LONGPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_HALL: 
                properties = EFX_REVERB_PRESET_CASTLE_HALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_CUPBOARD: 
                properties = EFX_REVERB_PRESET_CASTLE_CUPBOARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_COURTYARD: 
                properties = EFX_REVERB_PRESET_CASTLE_COURTYARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case CASTLE_ALCOVE: 
                properties = EFX_REVERB_PRESET_CASTLE_ALCOVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_SMALL_ROOM: 
                properties = EFX_REVERB_PRESET_FACTORY_SMALLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_SHORT_PASSAGE: 
                properties = EFX_REVERB_PRESET_FACTORY_SHORTPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_MEDIUM_ROOM: 
                properties = EFX_REVERB_PRESET_FACTORY_MEDIUMROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_LARGE_ROOM: 
                properties = EFX_REVERB_PRESET_FACTORY_LARGEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_LONG_PASSAGE: 
                properties = EFX_REVERB_PRESET_FACTORY_LONGPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_HALL: 
                properties = EFX_REVERB_PRESET_FACTORY_HALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_CUPBOARD: 
                properties = EFX_REVERB_PRESET_FACTORY_CUPBOARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_COURTYARD: 
                properties = EFX_REVERB_PRESET_FACTORY_COURTYARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case FACTORY_ALCOVE: 
                properties = EFX_REVERB_PRESET_FACTORY_ALCOVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_SMALL_ROOM: 
                properties = EFX_REVERB_PRESET_ICEPALACE_SMALLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_SHORT_PASSAGE: 
                properties = EFX_REVERB_PRESET_ICEPALACE_SHORTPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_MEDIUM_ROOM: 
                properties = EFX_REVERB_PRESET_ICEPALACE_MEDIUMROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_LARGE_ROOM: 
                properties = EFX_REVERB_PRESET_ICEPALACE_LARGEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_LONG_PASSAGE: 
                properties = EFX_REVERB_PRESET_ICEPALACE_LONGPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_HALL: 
                properties = EFX_REVERB_PRESET_ICEPALACE_HALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_CUPBOARD: 
                properties = EFX_REVERB_PRESET_ICEPALACE_CUPBOARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_COURTYARD: 
                properties = EFX_REVERB_PRESET_ICEPALACE_COURTYARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case ICE_PALACE_ALCOVE: 
                properties = EFX_REVERB_PRESET_ICEPALACE_ALCOVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_SMALL_ROOM: 
                properties = EFX_REVERB_PRESET_SPACESTATION_SMALLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_SHORT_PASSAGE: 
                properties = EFX_REVERB_PRESET_SPACESTATION_SHORTPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_MEDIUM_ROOM: 
                properties = EFX_REVERB_PRESET_SPACESTATION_MEDIUMROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_LARGE_ROOM: 
                properties = EFX_REVERB_PRESET_SPACESTATION_LARGEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_LONG_PASSAGE: 
                properties = EFX_REVERB_PRESET_SPACESTATION_LONGPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_HALL: 
                properties = EFX_REVERB_PRESET_SPACESTATION_HALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_CUPBOARD: 
                properties = EFX_REVERB_PRESET_SPACESTATION_CUPBOARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPACE_STATION_ALCOVE: 
                properties = EFX_REVERB_PRESET_SPACESTATION_ALCOVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_SMALL_ROOM: 
                properties = EFX_REVERB_PRESET_WOODEN_SMALLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_SHORT_PASSAGE: 
                properties = EFX_REVERB_PRESET_WOODEN_SHORTPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_MEDIUM_ROOM: 
                properties = EFX_REVERB_PRESET_WOODEN_MEDIUMROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_LARGE_ROOM: 
                properties = EFX_REVERB_PRESET_WOODEN_LARGEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_LONG_PASSAGE: 
                properties = EFX_REVERB_PRESET_WOODEN_LONGPASSAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_HALL: 
                properties = EFX_REVERB_PRESET_WOODEN_HALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_CUPBOARD: 
                properties = EFX_REVERB_PRESET_WOODEN_CUPBOARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_COURTYARD: 
                properties = EFX_REVERB_PRESET_WOODEN_COURTYARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case WOODEN_ALCOVE: 
                properties = EFX_REVERB_PRESET_WOODEN_ALCOVE;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_EMPTY_STADIUM: 
                properties = EFX_REVERB_PRESET_SPORT_EMPTYSTADIUM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_SQUASH_COURT: 
                properties = EFX_REVERB_PRESET_SPORT_SQUASHCOURT;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_SMALL_SWIMMING_POOL: 
                properties = EFX_REVERB_PRESET_SPORT_SMALLSWIMMINGPOOL;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_LARGE_SWIMMING_POOL: 
                properties = EFX_REVERB_PRESET_SPORT_LARGESWIMMINGPOOL;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_GYMNASIUM: 
                properties = EFX_REVERB_PRESET_SPORT_GYMNASIUM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_FULL_STADIUM: 
                properties = EFX_REVERB_PRESET_SPORT_FULLSTADIUM;
                loadFromEAXPreset(reverb, properties);
                break;
            case SPORT_STADIUM_TANNOY: 
                properties = EFX_REVERB_PRESET_SPORT_STADIUMTANNOY;
                loadFromEAXPreset(reverb, properties);
                break;
            case PREFAB_WORKSHOP: 
                properties = EFX_REVERB_PRESET_PREFAB_WORKSHOP;
                loadFromEAXPreset(reverb, properties);
                break;
            case PREFAB_SCHOOL_ROOM: 
                properties = EFX_REVERB_PRESET_PREFAB_SCHOOLROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case PREFAB_PRACTISE_ROOM: 
                properties = EFX_REVERB_PRESET_PREFAB_PRACTISEROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case PREFAB_OUTHOUSE: 
                properties = EFX_REVERB_PRESET_PREFAB_OUTHOUSE;
                loadFromEAXPreset(reverb, properties);
                break;
            case PREFAB_CARAVAN: 
                properties = EFX_REVERB_PRESET_PREFAB_CARAVAN;
                loadFromEAXPreset(reverb, properties);
                break;
            case DOME_TOMB: 
                properties = EFX_REVERB_PRESET_DOME_TOMB;
                loadFromEAXPreset(reverb, properties);
                break;
            case PIPE_SMALL: 
                properties = EFX_REVERB_PRESET_PIPE_SMALL;
                loadFromEAXPreset(reverb, properties);
                break;
            case DOME_SAINTPAULS: 
                properties = EFX_REVERB_PRESET_DOME_SAINTPAULS;
                loadFromEAXPreset(reverb, properties);
                break;
            case PIPE_LONG_THIN: 
                properties = EFX_REVERB_PRESET_PIPE_LONGTHIN;
                loadFromEAXPreset(reverb, properties);
                break;
            case PIPE_LARGE: 
                properties = EFX_REVERB_PRESET_PIPE_LARGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case PIPE_RESONANT: 
                properties = EFX_REVERB_PRESET_PIPE_RESONANT;
                loadFromEAXPreset(reverb, properties);
                break;
            case OUTDOORS_BACKYARD: 
                properties = EFX_REVERB_PRESET_OUTDOORS_BACKYARD;
                loadFromEAXPreset(reverb, properties);
                break;
            case OUTDOORS_ROLLING_PLAINS: 
                properties = EFX_REVERB_PRESET_OUTDOORS_ROLLINGPLAINS;
                loadFromEAXPreset(reverb, properties);
                break;
            case OUTDOORS_DEEP_CANYON: 
                properties = EFX_REVERB_PRESET_OUTDOORS_DEEPCANYON;
                loadFromEAXPreset(reverb, properties);
                break;
            case OUTDOORS_CREEK: 
                properties = EFX_REVERB_PRESET_OUTDOORS_CREEK;
                loadFromEAXPreset(reverb, properties);
                break;
            case OUTDOORS_VALLEY: 
                properties = EFX_REVERB_PRESET_OUTDOORS_VALLEY;
                loadFromEAXPreset(reverb, properties);
                break;
            case MOOD_HEAVEN: 
                properties = EFX_REVERB_PRESET_MOOD_HEAVEN;
                loadFromEAXPreset(reverb, properties);
                break;
            case MOOD_HELL: 
                properties = EFX_REVERB_PRESET_MOOD_HELL;
                loadFromEAXPreset(reverb, properties);
                break;
            case MOOD_MEMORY: 
                properties = EFX_REVERB_PRESET_MOOD_MEMORY;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_COMMENTATOR: 
                properties = EFX_REVERB_PRESET_DRIVING_COMMENTATOR;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_PIT_GARAGE: 
                properties = EFX_REVERB_PRESET_DRIVING_PITGARAGE;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_INCAR_RACER: 
                properties = EFX_REVERB_PRESET_DRIVING_INCAR_RACER;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_INCAR_SPORTS: 
                properties = EFX_REVERB_PRESET_DRIVING_INCAR_SPORTS;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_INCAR_LUXURY: 
                properties = EFX_REVERB_PRESET_DRIVING_INCAR_LUXURY;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_FULL_GRAND_STAND: 
                properties = EFX_REVERB_PRESET_DRIVING_FULLGRANDSTAND;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_EMPTY_GRAND_STAND: 
                properties = EFX_REVERB_PRESET_DRIVING_EMPTYGRANDSTAND;
                loadFromEAXPreset(reverb, properties);
                break;
            case DRIVING_TUNNEL: 
                properties = EFX_REVERB_PRESET_DRIVING_TUNNEL;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_STREETS: 
                properties = EFX_REVERB_PRESET_CITY_STREETS;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_SUBWAY: 
                properties = EFX_REVERB_PRESET_CITY_SUBWAY;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_MUSEUM: 
                properties = EFX_REVERB_PRESET_CITY_MUSEUM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_LIBRARY: 
                properties = EFX_REVERB_PRESET_CITY_LIBRARY;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_UNDERPASS: 
                properties = EFX_REVERB_PRESET_CITY_UNDERPASS;
                loadFromEAXPreset(reverb, properties);
                break;
            case CITY_ABANDONED: 
                properties = EFX_REVERB_PRESET_CITY_ABANDONED;
                loadFromEAXPreset(reverb, properties);
                break;
            case DUSTY_ROOM: 
                properties = EFX_REVERB_PRESET_DUSTYROOM;
                loadFromEAXPreset(reverb, properties);
                break;
            case CHAPEL: 
                properties = EFX_REVERB_PRESET_CHAPEL;
                loadFromEAXPreset(reverb, properties);
                break;
            case SMALL_WATER_ROOM: 
                properties = EFX_REVERB_PRESET_SMALLWATERROOM;
                loadFromEAXPreset(reverb, properties);
                break;
        }
    }
}

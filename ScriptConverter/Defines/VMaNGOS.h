#include "Common.h"

#define MAX_TEXT_ID 4
#define MAX_EMOTE_ID 4
#define UNIT_FIELD_FLAGS 46

namespace VMaNGOS
{

    enum EventAI_Type
    {
        EVENT_T_TIMER                   = 0,                    // InitialMin, InitialMax, RepeatMin, RepeatMax
        EVENT_T_TIMER_OOC               = 1,                    // InitialMin, InitialMax, RepeatMin, RepeatMax
        EVENT_T_HP                      = 2,                    // HPMax%, HPMin%, RepeatMin, RepeatMax
        EVENT_T_MANA                    = 3,                    // ManaMax%,ManaMin% RepeatMin, RepeatMax
        EVENT_T_AGGRO                   = 4,                    // NONE
        EVENT_T_KILL                    = 5,                    // RepeatMin, RepeatMax
        EVENT_T_DEATH                   = 6,                    // NONE
        EVENT_T_EVADE                   = 7,                    // NONE
        EVENT_T_SPELLHIT                = 8,                    // SpellID, School, RepeatMin, RepeatMax
        EVENT_T_RANGE                   = 9,                    // MinDist, MaxDist, RepeatMin, RepeatMax
        EVENT_T_OOC_LOS                 = 10,                   // NoHostile, MaxRnage, RepeatMin, RepeatMax
        EVENT_T_SPAWNED                 = 11,                   // NONE
        EVENT_T_TARGET_HP               = 12,                   // HPMax%, HPMin%, RepeatMin, RepeatMax
        EVENT_T_TARGET_CASTING          = 13,                   // RepeatMin, RepeatMax
        EVENT_T_FRIENDLY_HP             = 14,                   // HPDeficit, Radius, RepeatMin, RepeatMax
        EVENT_T_FRIENDLY_IS_CC          = 15,                   // DispelType, Radius, RepeatMin, RepeatMax
        EVENT_T_FRIENDLY_MISSING_BUFF   = 16,                   // SpellId, Radius, RepeatMin, RepeatMax
        EVENT_T_SUMMONED_UNIT           = 17,                   // CreatureId, RepeatMin, RepeatMax
        EVENT_T_TARGET_MANA             = 18,                   // ManaMax%, ManaMin%, RepeatMin, RepeatMax
        EVENT_T_QUEST_ACCEPT            = 19,                   // QuestID
        EVENT_T_QUEST_COMPLETE          = 20,                   //
        EVENT_T_REACHED_HOME            = 21,                   // NONE
        EVENT_T_RECEIVE_EMOTE           = 22,                   // EmoteId
        EVENT_T_AURA                    = 23,                   // Param1 = SpellID, Param2 = Number of time stacked, Param3/4 Repeat Min/Max
        EVENT_T_TARGET_AURA             = 24,                   // Param1 = SpellID, Param2 = Number of time stacked, Param3/4 Repeat Min/Max
        EVENT_T_SUMMONED_JUST_DIED      = 25,                   // CreatureId, RepeatMin, RepeatMax
        EVENT_T_SUMMONED_JUST_DESPAWN   = 26,                   // CreatureId, RepeatMin, RepeatMax
        EVENT_T_MISSING_AURA            = 27,                   // Param1 = SpellID, Param2 = Number of time stacked expected, Param3/4 Repeat Min/Max
        EVENT_T_TARGET_MISSING_AURA     = 28,                   // Param1 = SpellID, Param2 = Number of time stacked expected, Param3/4 Repeat Min/Max
        EVENT_T_MOVEMENT_INFORM         = 29,                   // Param1 = motion type, Param2 = point ID, RepeatMin, RepeatMax
        EVENT_T_LEAVE_COMBAT            = 30,                   // NONE
        EVENT_T_MAP_SCRIPT_EVENT        = 31,                   // Param1 = EventID, Param2 = Data
        EVENT_T_GROUP_MEMBER_DIED       = 32,                   // Param1 = CreatureId, Param2 = IsLeader

        EVENT_T_END,
    };

    enum EventFlags
    {
        EFLAG_REPEATABLE            = 0x01,                     //Event repeats
        EFLAG_RANDOM_ACTION         = 0x02,                     //Event only execute one from existed actions instead each action.
        EFLAG_DEBUG_ONLY            = 0x04,                     //Event only occurs in debug build
        // uint8 field
    };

    enum eScriptCommand
    {
        SCRIPT_COMMAND_TALK                     = 0,            // source = WorldObject
                                                                // target = Unit/None
                                                                // datalong = chat_type (see enum ChatType)
                                                                // dataint = broadcast_text id. dataint2-4 optional for random selected text.
        SCRIPT_COMMAND_EMOTE                    = 1,            // source = Unit
                                                                // datalong = emote_id
        SCRIPT_COMMAND_FIELD_SET                = 2,            // source = Object
                                                                // datalong = field_id
                                                                // datalong2 = value
        SCRIPT_COMMAND_MOVE_TO                  = 3,            // source = Creature
                                                                // target = WorldObject (for datalong > 0)
                                                                // datalong = coordinates_type (see enum eMoveToCoordinateTypes)
                                                                // datalong2 = time
                                                                // datalong3 = movement_options (see enum MoveOptions)
                                                                // datalong4 = eMoveToFlags
                                                                // dataint = path_id
                                                                // x/y/z/o = coordinates
        SCRIPT_COMMAND_MODIFY_FLAGS             = 4,            // source = Object
                                                                // datalong = field_id
                                                                // datalong2 = bitmask
                                                                // datalong3 = eModifyFlagsOptions
        SCRIPT_COMMAND_INTERRUPT_CASTS          = 5,            // source = Unit
                                                                // datalong = (bool) with_delayed
                                                                // datalong2 = spell_id (optional)
        SCRIPT_COMMAND_TELEPORT_TO              = 6,            // source = Unit
                                                                // datalong = map_id (only used for players but still required)
                                                                // datalong2 = teleport_options (see enum TeleportToOptions)
                                                                // x/y/z/o = coordinates
        SCRIPT_COMMAND_QUEST_EXPLORED           = 7,            // source = Player (from provided source or target)
                                                                // target = WorldObject (from provided source or target)
                                                                // datalong = quest_id
                                                                // datalong2 = distance or 0
                                                                // datalong3 = (bool) group
        SCRIPT_COMMAND_KILL_CREDIT              = 8,            // source = Player (from provided source or target)
                                                                // datalong = creature entry
                                                                // datalong2 = bool (0=personal credit, 1=group credit)
        SCRIPT_COMMAND_RESPAWN_GAMEOBJECT       = 9,            // source = Map
                                                                // target = GameObject (from datalong, provided source or target)
                                                                // datalong = db_guid
                                                                // datalong2 = despawn_delay
        SCRIPT_COMMAND_TEMP_SUMMON_CREATURE     = 10,           // source = WorldObject (from provided source or buddy)
                                                                // datalong = creature_entry
                                                                // datalong2 = despawn_delay
                                                                // datalong3 = unique_limit
                                                                // datalong4 = unique_distance
                                                                // dataint = eSummonCreatureFlags
                                                                // dataint2 = script_id
                                                                // dataint3 = attack_target (see enum Target)
                                                                // dataint4 = despawn_type (see enum TempSummonType)
                                                                // x/y/z/o = coordinates
        SCRIPT_COMMAND_OPEN_DOOR                = 11,           // source = GameObject (from datalong, provided source or target)
                                                                // If provided target is BUTTON GameObject, command is run on it too.
                                                                // datalong = db_guid
                                                                // datalong2 = reset_delay
        SCRIPT_COMMAND_CLOSE_DOOR               = 12,           // source = GameObject (from datalong, provided source or target)
                                                                // If provided target is BUTTON GameObject, command is run on it too.
                                                                // datalong = db_guid
                                                                // datalong2 = reset_delay
        SCRIPT_COMMAND_ACTIVATE_OBJECT          = 13,           // source = GameObject
                                                                // target = Unit
        SCRIPT_COMMAND_REMOVE_AURA              = 14,           // source = Unit
                                                                // datalong = spell_id
        SCRIPT_COMMAND_CAST_SPELL               = 15,           // source = Unit
                                                                // target = Unit
                                                                // datalong = spell_id
                                                                // datalong2 = eCastSpellFlags
        SCRIPT_COMMAND_PLAY_SOUND               = 16,           // source = WorldObject
                                                                // target = Player/None
                                                                // datalong = sound_id
                                                                // datalong2 = ePlaySoundFlags
        SCRIPT_COMMAND_CREATE_ITEM              = 17,           // source = Player (from provided source or target)
                                                                // datalong = item_entry
                                                                // datalong2 = amount
        SCRIPT_COMMAND_DESPAWN_CREATURE         = 18,           // source = Creature
                                                                // datalong = despawn_delay
        SCRIPT_COMMAND_SET_EQUIPMENT            = 19,           // source = Creature
                                                                // datalong = (bool) reset_default
                                                                // dataint = main-hand item_id
                                                                // dataint2 = off-hand item_id
                                                                // dataint3 = ranged item_id
        SCRIPT_COMMAND_MOVEMENT                 = 20,           // source = Creature
                                                                // datalong = see enum MovementGeneratorType (not all are supported)
                                                                // datalong2 = bool_param (meaning depends on the motion type)
                                                                // datalong3 = int_param (meaning depends on the motion type)
                                                                // datalong4 = (bool) clear
                                                                // x = distance (only for some motion types)
                                                                // o = angle (only for some motion types)
        SCRIPT_COMMAND_SET_ACTIVEOBJECT         = 21,           // source = Creature
                                                                // datalong = (bool) 0=off, 1=on
        SCRIPT_COMMAND_SET_FACTION              = 22,           // source = Creature
                                                                // datalong = faction_Id,
                                                                // datalong2 = see enum TemporaryFactionFlags
        SCRIPT_COMMAND_MORPH_TO_ENTRY_OR_MODEL  = 23,           // source = Creature
                                                                // datalong = creature entry/modelid (depend on datalong2)
                                                                // datalong2 = (bool) is_display_id
        SCRIPT_COMMAND_MOUNT_TO_ENTRY_OR_MODEL  = 24,           // source = Creature
                                                                // datalong = creature entry/modelid (depend on datalong2)
                                                                // datalong2 = (bool) is_display_id
                                                                // datalong3 = (bool) permanent
        SCRIPT_COMMAND_SET_RUN                  = 25,           // source = Creature
                                                                // datalong = (bool) 0 = off, 1 = on
        SCRIPT_COMMAND_ATTACK_START             = 26,           // source = Creature
                                                                // target = Player
        SCRIPT_COMMAND_UPDATE_ENTRY             = 27,           // source = Creature
                                                                // datalong = creature_entry
                                                                // datalong2 = team for display_id (0 = alliance, 1 = horde)
        SCRIPT_COMMAND_STAND_STATE              = 28,           // source = Unit
                                                                // datalong = stand_state (enum UnitStandStateType)
        SCRIPT_COMMAND_MODIFY_THREAT            = 29,           // source = Creature
                                                                // datalong = eModifyThreatTargets
                                                                // x = percent
        SCRIPT_COMMAND_SEND_TAXI_PATH           = 30,           // source = Player
                                                                // datalong = taxi_path_id
        SCRIPT_COMMAND_TERMINATE_SCRIPT         = 31,           // source = Any
                                                                // datalong = creature_entry
                                                                // datalong2 = search_distance
                                                                // datalong3 = eTerminateScriptOptions
        SCRIPT_COMMAND_TERMINATE_CONDITION      = 32,           // source = Any
                                                                // datalong = condition_id
                                                                // datalong2 = failed_quest_id
                                                                // datalong3 = eTerminateConditionFlags
        SCRIPT_COMMAND_ENTER_EVADE_MODE         = 33,           // source = Creature
        SCRIPT_COMMAND_SET_HOME_POSITION        = 34,           // source = Creature
                                                                // datalong = eSetHomePositionOptions
                                                                // x/y/z/o = coordinates
        SCRIPT_COMMAND_TURN_TO                  = 35,           // source = Unit
                                                                // target = WorldObject
                                                                // datalong = eTurnToFacingOptions
        SCRIPT_COMMAND_MEETINGSTONE             = 36,           // source = Player
                                                                // datalong = area_id
        SCRIPT_COMMAND_SET_INST_DATA            = 37,           // source = Map
                                                                // datalong = field
                                                                // datalong2 = data
                                                                // datalong3 = eSetInstDataOptions
        SCRIPT_COMMAND_SET_INST_DATA64          = 38,           // source = Map
                                                                // target = Object (when saving guid)
                                                                // datalong = field
                                                                // datalong2 = data
                                                                // datalong3 = eSetInstData64Options
        SCRIPT_COMMAND_START_SCRIPT             = 39,           // source = Map
                                                                // datalong1-4 = event_script id
                                                                // dataint1-4 = chance (total cant be above 100)
        SCRIPT_COMMAND_REMOVE_ITEM              = 40,           // source = Player (from provided source or target)
                                                                // datalong = item_entry
                                                                // datalong2 = amount
        SCRIPT_COMMAND_REMOVE_OBJECT            = 41,           // source = GameObject
                                                                // target = Unit
        SCRIPT_COMMAND_SET_MELEE_ATTACK         = 42,           // source = Creature
                                                                // datalong = (bool) 0 = off, 1 = on
        SCRIPT_COMMAND_SET_COMBAT_MOVEMENT      = 43,           // source = Creature
                                                                // datalong = (bool) 0 = off, 1 = on
        SCRIPT_COMMAND_SET_PHASE                = 44,           // source = Creature
                                                                // datalong = phase
                                                                // datalong2 = eSetPhaseOptions
        SCRIPT_COMMAND_SET_PHASE_RANDOM         = 45,           // source = Creature
                                                                // datalong1-4 = phase
        SCRIPT_COMMAND_SET_PHASE_RANGE          = 46,           // source = Creature
                                                                // datalong = phase_min
                                                                // datalong2 = phase_max
        SCRIPT_COMMAND_FLEE                     = 47,           // source = Creature
                                                                // datalong = seek_assistance (bool) 0 = off, 1 = on
        SCRIPT_COMMAND_DEAL_DAMAGE              = 48,           // source = Unit
                                                                // target = Unit
                                                                // datalong = damage
                                                                // datalong2 = (bool) is_percent
        SCRIPT_COMMAND_ZONE_COMBAT_PULSE        = 49,           // source = Creature
                                                                // datalong = (bool) initialPulse
        SCRIPT_COMMAND_CALL_FOR_HELP            = 50,           // source = Creature
                                                                // x = radius
        SCRIPT_COMMAND_SET_SHEATH               = 51,           // source = Unit
                                                                // datalong = see enum SheathState
        SCRIPT_COMMAND_INVINCIBILITY            = 52,           // source = Creature
                                                                // datalong = health
                                                                // datalong2 = (bool) is_percent
        SCRIPT_COMMAND_GAME_EVENT               = 53,           // source = None
                                                                // datalong = event_id
                                                                // datalong2 = (bool) start
                                                                // datalong3 = (bool) overwrite
        SCRIPT_COMMAND_SET_SERVER_VARIABLE      = 54,           // source = None
                                                                // datalong = index
                                                                // datalong2 = value
        SCRIPT_COMMAND_CREATURE_SPELLS          = 55,           // source = Creature
                                                                // datalong1-4 = creature_spells id
                                                                // dataint1-4 = chance (total cant be above 100)
        SCRIPT_COMMAND_REMOVE_GUARDIANS         = 56,           // source = Unit
                                                                // datalong = creature_id
        SCRIPT_COMMAND_ADD_SPELL_COOLDOWN       = 57,           // source = Unit
                                                                // datalong = spell_id
                                                                // datalong2 = cooldown
        SCRIPT_COMMAND_REMOVE_SPELL_COOLDOWN    = 58,           // source = Unit
                                                                // datalong = spell_id
        SCRIPT_COMMAND_SET_REACT_STATE          = 59,           // source = Creature
                                                                // datalong = see enum ReactStates
        SCRIPT_COMMAND_START_WAYPOINTS          = 60,           // source = Creature
                                                                // datalong = waypoints_source
                                                                // datalong2 = start_point
                                                                // datalong3 = initial_delay
                                                                // datalong4 = (bool) repeat
                                                                // dataint = path_id
                                                                // dataint2 = overwrite_entry
        SCRIPT_COMMAND_START_MAP_EVENT          = 61,           // source = Map
                                                                // datalong = event_id
                                                                // datalong2 = time_limit
                                                                // dataint = success_condition
                                                                // dataint2 = success_script
                                                                // dataint3 = failure_condition
                                                                // dataint4 = failure_script
        SCRIPT_COMMAND_END_MAP_EVENT            = 62,           // source = Map
                                                                // datalong = event_id
                                                                // datalong2 = (bool) success
        SCRIPT_COMMAND_ADD_MAP_EVENT_TARGET     = 63,           // source = Map
                                                                // target = WorldObject
                                                                // datalong = event_id
                                                                // dataint = success_condition
                                                                // dataint2 = success_script
                                                                // dataint3 = failure_condition
                                                                // dataint4 = failure_script
        SCRIPT_COMMAND_REMOVE_MAP_EVENT_TARGET  = 64,           // source = Map
                                                                // target = WorldObject
                                                                // datalong = event_id
                                                                // datalong2 = condition_id
                                                                // datalong3 = eRemoveMapEventTargetOptions
        SCRIPT_COMMAND_SET_MAP_EVENT_DATA       = 65,           // source = Map
                                                                // datalong = event_id
                                                                // datalong2 = index
                                                                // datalong3 = data
                                                                // datalong4 = eSetMapScriptDataOptions
        SCRIPT_COMMAND_SEND_MAP_EVENT           = 66,           // source = Map
                                                                // datalong = event_id
                                                                // datalong2 = data
                                                                // datalong3 = eSendMapEventOptions
        SCRIPT_COMMAND_SET_DEFAULT_MOVEMENT     = 67,           // source = Creature
                                                                // datalong = movement_type
                                                                // datalong2 = (bool) always_replace
                                                                // datalong3 = param1
        SCRIPT_COMMAND_START_SCRIPT_FOR_ALL     = 68,           // source = WorldObject
                                                                // datalong = script_id
                                                                // datalong2 = eStartScriptForAllOptions
                                                                // datalong3 = object_entry
                                                                // datalong4 = search_radius
        SCRIPT_COMMAND_EDIT_MAP_EVENT           = 69,           // source = Map
                                                                // datalong = event_id
                                                                // dataint = success_condition
                                                                // dataint2 = success_script
                                                                // dataint3 = failure_condition
                                                                // dataint4 = failure_script
        SCRIPT_COMMAND_FAIL_QUEST               = 70,           // source = Player
                                                                // datalong = quest_id
        SCRIPT_COMMAND_RESPAWN_CREATURE         = 71,           // source = Creature
                                                                // datalong = (bool) even_if_alive
        SCRIPT_COMMAND_ASSIST_UNIT              = 72,           // source = Creature
                                                                // target = Unit
        SCRIPT_COMMAND_COMBAT_STOP              = 73,           // source = Unit
        SCRIPT_COMMAND_ADD_AURA                 = 74,           // source = Unit
                                                                // datalong = spell_id
                                                                // datalong2 = flags
        SCRIPT_COMMAND_ADD_THREAT               = 75,           // source = Creature
                                                                // target = Unit
    
        SCRIPT_COMMAND_MAX,

        SCRIPT_COMMAND_DISABLED                 = 9999          // Script action was disabled during loading.
    };

    // Flags used by SCRIPT_COMMAND_MOVE_TO
    enum eMoveToFlags
    {
        SF_MOVETO_FORCED        = 0x1,                          // No check if creature can move.
        SF_MOVETO_POINT_MOVEGEN = 0x2,                          // Changes movement generator to point movement.
    };

    // Possible datalong3 values for SCRIPT_COMMAND_MOVE_TO
    enum eMoveToCoordinateTypes
    {
        SO_MOVETO_COORDINATES_NORMAL               = 0,
        SO_MOVETO_COORDINATES_RELATIVE_TO_TARGET   = 1,            // Coordinates are added to that of target.
        SO_MOVETO_COORDINATES_DISTANCE_FROM_TARGET = 2,            // X is distance from target, others not used.

        MOVETO_COORDINATES_MAX
    };

    // Possible datalong3 values for SCRIPT_COMMAND_MODIFY_FLAGS
    enum eModifyFlagsOptions
    {
        SO_MODIFYFLAGS_TOGGLE = 0,
        SO_MODIFYFLAGS_SET    = 1,
        SO_MODIFYFLAGS_REMOVE = 2
    };

    // Flags used by SCRIPT_COMMAND_TEMP_SUMMON_CREATURE
    // Must start from 0x8 because of target selection flags.
    enum eSummonCreatureFlags
    {
        SF_SUMMONCREATURE_SET_RUN     = 0x1,                         // makes creature move at run speed
        SF_SUMMONCREATURE_ACTIVE      = 0x2,                         // active creatures are always updated
        SF_SUMMONCREATURE_UNIQUE      = 0x4,                         // not actually unique, just checks for same entry in certain range
        SF_SUMMONCREATURE_UNIQUE_TEMP = 0x8                          // same as 0x10 but check for TempSummon only creatures
    };

    // Flags used by SCRIPT_COMMAND_PLAY_SOUND
    enum ePlaySoundFlags
    {
        SF_PLAYSOUND_ONLY_TO_TARGET     = 0x1,
        SF_PLAYSOUND_DISTANCE_DEPENDENT = 0x2
    };

    // Possible datalong values for SCRIPT_COMMAND_MODIFY_THREAT
    enum eModifyThreatTargets
    {
        // 0 to 5 from Target enum.
        SO_MODIFYTHREAT_ALL_ATTACKERS   = 6
    };

    // Possible datalong3 values for SCRIPT_COMMAND_TERMINATE_SCRIPT
    enum eTerminateScriptOptions
    {
        SO_TERMINATESCRIPT_IF_NOT_FOUND = 0,
        SO_TERMINATESCRIPT_IF_FOUND     = 1
    };

    // Flags used by SCRIPT_COMMAND_TERMINATE_CONDITION
    enum eTerminateConditionFlags
    {
        SF_TERMINATECONDITION_WHEN_FALSE = 0x1
    };

    // Possible datalong values for SCRIPT_COMMAND_SET_HOME_POSITION
    enum eSetHomePositionOptions
    {
        SO_SETHOME_PROVIDED_POSITION = 0,
        SO_SETHOME_CURRENT_POSITION  = 1,
        SO_SETHOME_DEFAULT_POSITION  = 2
    };

    // Possible datalong values for SCRIPT_COMMAND_TURN_TO
    enum eTurnToFacingOptions
    {
        SO_TURNTO_FACE_TARGET          = 0,
        SO_TURNTO_PROVIDED_ORIENTATION = 1
    };

    // Possible datalong3 values for SCRIPT_COMMAND_SET_INST_DATA
    enum eSetInstDataOptions
    {
        SO_INSTDATA_RAW       = 0,
        SO_INSTDATA_INCREMENT = 1,
        SO_INSTDATA_DECREMENT = 2,

        SO_INSTDATA_MAX
    };

    // Possible datalong3 values for SCRIPT_COMMAND_SET_INST_DATA64
    enum eSetInstData64Options
    {
        SO_INSTDATA64_RAW         = 0,
        SO_INSTDATA64_SOURCE_GUID = 1,

        SO_INSTDATA64_MAX
    };

    // Possible datalong values for SCRIPT_COMMAND_SET_PHASE
    enum eSetPhaseOptions
    {
        SO_SETPHASE_RAW       = 0,
        SO_SETPHASE_INCREMENT = 1,
        SO_SETPHASE_DECREMENT = 2,

        SO_SETPHASE_MAX
    };

    // Possible datalong3 values for SCRIPT_COMMAND_REMOVE_MAP_EVENT_TARGET
    enum eRemoveMapEventTargetOptions
    {
        SO_REMOVETARGET_SELF = 0,
        SO_REMOVETARGET_ONE_FIT_CONDITION = 1,
        SO_REMOVETARGET_ALL_FIT_CONDITION = 2,
        SO_REMOVETARGET_ALL_TARGETS = 3,

        SO_REMOVETARGET_MAX
    };

    // Possible datalong4 values for SCRIPT_COMMAND_SET_MAP_EVENT_DATA
    enum eSetMapScriptDataOptions
    {
        SO_MAPEVENTDATA_RAW       = 0,
        SO_MAPEVENTDATA_INCREMENT = 1,
        SO_MAPEVENTDATA_DECREMENT = 2,

        SO_MAPEVENTDATA_MAX
    };

    // Possible datalong3 values for SCRIPT_COMMAND_SEND_MAP_EVENT
    enum eSendMapEventOptions
    {
        SO_SENDMAPEVENT_MAIN_TARGETS_ONLY  = 0,
        SO_SENDMAPEVENT_EXTRA_TARGETS_ONLY = 1,
        SO_SENDMAPEVENT_ALL_TARGETS        = 2,

        SO_SENDMAPEVENT_MAX
    };

    // Possible datalong2 values for SCRIPT_COMMAND_START_SCRIPT_FOR_ALL
    enum eStartScriptForAllOptions
    {
        SO_STARTFORALL_GAMEOBJECTS  = 0,
        SO_STARTFORALL_UNITS        = 1,
        SO_STARTFORALL_CREATURES    = 2,
        SO_STARTFORALL_PLAYERS      = 3,

        SO_STARTFORALL_MAX
    };

    enum eDataFlags
    {
        SF_GENERAL_SWAP_INITIAL_TARGETS = 0x1,                  // Swaps the provided source and target, before buddy is checked.
        SF_GENERAL_SWAP_FINAL_TARGETS   = 0x2,                  // Swaps the local source and target, after buddy is assigned.
        SF_GENERAL_TARGET_SELF          = 0x4,                  // Replaces the provided target with the provided source.
        SF_GENERAL_ABORT_ON_FAILURE     = 0x8                   // Terminates the script if the command fails.
    };

    struct ScriptInfo
    {
        uint32 id;
        uint32 delay;
        uint32 command;
        uint32 condition;

        union
        {
            struct                                              // SCRIPT_COMMAND_TALK (0)
            {
                uint32 chatType;                                // datalong
                uint32 unused1;                                 // datalong2
                uint32 unused2;                                 // datalong3
                uint32 unused3;                                 // datalong4
                uint32 unused4;                                 // data_flags
                int32  textId[MAX_TEXT_ID];                     // dataint to dataint4
            } talk;

            struct                                              // SCRIPT_COMMAND_EMOTE (1)
            {
                uint32 emoteId;                                 // datalong
                uint32 unused1;                                 // datalong2
                uint32 unused2;                                 // datalong3
                uint32 unused3;                                 // datalong4
                uint32 unused4;                                 // data_flags
                uint32 randomEmotes[MAX_EMOTE_ID];              // dataint to dataint4
            } emote;

            struct                                              // SCRIPT_COMMAND_FIELD_SET (2)
            {
                uint32 fieldId;                                 // datalong
                uint32 fieldValue;                              // datalong2
            } setField;

            struct                                              // SCRIPT_COMMAND_MOVE_TO (3)
            {
                uint32 coordinatesType;                         // datalong
                uint32 travelTime;                              // datalong2
                uint32 movementOptions;                         // datalong3
                uint32 flags;                                   // datalong4
                uint32 unused;                                  // data_flags
                int32 pointId;                                  // dataint
            } moveTo;

            struct                                              // SCRIPT_COMMAND_MODIFY_FLAGS (4)
            {
                uint32 fieldId;                                 // datalong
                uint32 fieldValue;                              // datalong2
                uint32 mode;                                    // datalong3
            } modFlags;

            struct                                              // SCRIPT_COMMAND_INTERRUPT_CASTS (5)
            {
                uint32 withDelayed;                             // datalong
                uint32 spellId;                                 // datalong2
            } interruptCasts;

            struct                                              // SCRIPT_COMMAND_TELEPORT_TO (6)
            {
                uint32 mapId;                                   // datalong
                uint32 teleportOptions;                         // datalong2
            } teleportTo;

            struct                                              // SCRIPT_COMMAND_QUEST_EXPLORED (7)
            {
                uint32 questId;                                 // datalong
                uint32 distance;                                // datalong2
                uint32 group;                                   // datalong3
            } questExplored;

            struct                                              // SCRIPT_COMMAND_KILL_CREDIT (8)
            {
                uint32 creatureEntry;                           // datalong
                uint32 isGroupCredit;                           // datalong2
            } killCredit;

            struct                                              // SCRIPT_COMMAND_RESPAWN_GAMEOBJECT (9)
            {
                uint32 goGuid;                                  // datalong
                int32 despawnDelay;                             // datalong2
            } respawnGo;

            struct                                              // SCRIPT_COMMAND_TEMP_SUMMON_CREATURE (10)
            {
                uint32 creatureEntry;                           // datalong
                uint32 despawnDelay;                            // datalong2
                uint32 uniqueLimit;                             // datalong3
                uint32 uniqueDistance;                          // datalong4
                uint32 unused;                                  // data_flags
                int32 flags;                                    // dataint
                int32 scriptId;                                 // dataint2
                int32 attackTarget;                             // dataint3
                int32 despawnType;                              // dataint4
            } summonCreature;

            struct                                              // SCRIPT_COMMAND_OPEN_DOOR (11)
            {
                uint32 goGuid;                                  // datalong
                int32 resetDelay;                               // datalong2
            } openDoor;

            struct                                              // SCRIPT_COMMAND_CLOSE_DOOR (12)
            {
                uint32 goGuid;                                  // datalong
                int32 resetDelay;                               // datalong2
            } closeDoor;

                                                                // SCRIPT_COMMAND_ACTIVATE_OBJECT (13)

            struct                                              // SCRIPT_COMMAND_REMOVE_AURA (14)
            {
                uint32 spellId;                                 // datalong
            } removeAura;

            struct                                              // SCRIPT_COMMAND_CAST_SPELL (15)
            {
                uint32 spellId;                                 // datalong
                uint32 flags;                                   // datalong2
            } castSpell;

            struct                                              // SCRIPT_COMMAND_PLAY_SOUND (16)
            {
                uint32 soundId;                                 // datalong
                uint32 flags;                                   // datalong2
            } playSound;

            struct                                              // SCRIPT_COMMAND_CREATE_ITEM (17)
            {
                uint32 itemEntry;                               // datalong
                uint32 amount;                                  // datalong2
            } createItem;

            struct                                              // SCRIPT_COMMAND_DESPAWN_CREATURE (18)
            {
                uint32 despawnDelay;                            // datalong
            } despawn;

            struct                                              // SCRIPT_COMMAND_SET_EQUIPMENT (19)
            {
                uint32 resetDefault;                            // datalong
                uint32 unused1;                                 // datalong2
                uint32 unused2;                                 // datalong3
                uint32 unused3;                                 // datalong4
                uint32 unused4;                                 // data_flags
                int32  slot[MAX_TEXT_ID];                       // dataint to dataint4
            } setEquipment;

            struct                                              // SCRIPT_COMMAND_MOVEMENT (20)
            {
                uint32 movementType;                            // datalong
                uint32 boolParam;                               // datalong2
                uint32 intParam;                                // datalong3
                uint32 clear;                                   // datalong4
            } movement;

            struct                                              // SCRIPT_COMMAND_SET_ACTIVEOBJECT (21)
            {
                uint32 activate;                                // datalong
            } activeObject;

            struct                                              // SCRIPT_COMMAND_SET_FACTION (22)
            {
                uint32 factionId;                               // datalong
                uint32 flags;                                   // datalong2
            } faction;

            struct                                              // SCRIPT_COMMAND_MORPH_TO_ENTRY_OR_MODEL (23)
            {
                uint32 creatureOrModelEntry;                    // datalong
                uint32 isDisplayId;                             // datalong2
            } morph;

            struct                                              // SCRIPT_COMMAND_MOUNT_TO_ENTRY_OR_MODEL (24)
            {
                uint32 creatureOrModelEntry;                    // datalong
                uint32 isDisplayId;                             // datalong2
                uint32 permanent;                               // datalong3
            } mount;

            struct                                              // SCRIPT_COMMAND_SET_RUN (25)
            {
                uint32 run;                                     // datalong
            } run;

                                                                // SCRIPT_COMMAND_ATTACK_START (26)

            struct                                              // SCRIPT_COMMAND_UPDATE_ENTRY (27)
            {
                uint32 creatureEntry;                           // datalong
                uint32 team;                                    // datalong2
            } updateEntry;

            struct                                              // SCRIPT_COMMAND_STAND_STATE (28)
            {
                uint32 standState;                             // datalong
            } standState;

            struct                                              // SCRIPT_COMMAND_MODIFY_THREAT (29)
            {
                uint32 target;                                  // datalong
            } modThreat;

            struct                                              // SCRIPT_COMMAND_SEND_TAXI_PATH (30)
            {
                uint32 taxiPathId;                              // datalong
            } sendTaxiPath;

            struct                                              // SCRIPT_COMMAND_TERMINATE_SCRIPT (31)
            {
                uint32 creatureEntry;                           // datalong
                uint32 searchRadius;                            // datalong2
                uint32 flags;                                   // datalong3
            } terminateScript;

            struct                                              // SCRIPT_COMMAND_TERMINATE_CONDITION (32)
            {
                uint32 conditionId;                             // datalong
                uint32 failQuest;                               // datalong2
                uint32 flags;                                   // datalong3
            } terminateCond;

                                                                // SCRIPT_COMMAND_ENTER_EVADE_MODE (33)

            struct                                              // SCRIPT_COMMAND_SET_HOME_POSITION (34)
            {
                uint32 mode;                                    // datalong
            } setHome;

            struct                                              // SCRIPT_COMMAND_TURN_TO (35)
            {
                uint32 facingLogic;                             // datalong
            } turnTo;

            struct                                              // SCRIPT_COMMAND_MEETINGSTONE (36)
            {
                uint32 areaId;                                  // datalong
            } meetingstone;

            struct                                              // SCRIPT_COMMAND_SET_INST_DATA (37)
            {
                uint32 field;                                   // datalong
                uint32 data;                                    // datalong2
                uint32 type;                                    // datalong3
            } setData;

            struct                                              // SCRIPT_COMMAND_SET_INST_DATA64 (38)
            {
                uint32 field;                                   // datalong
                uint32 data;                                    // datalong2
                uint32 type;                                    // datalong3
            } setData64;

            struct                                              // SCRIPT_COMMAND_START_SCRIPT (39)
            {
                uint32 scriptId[4];                             // datalong to datalong4
                uint32 unused;                                  // data_flags
                int32 chance[4];                                // dataint to dataint4
            } startScript;

            struct                                              // SCRIPT_COMMAND_REMOVE_ITEM (40)
            {
                uint32 itemEntry;                               // datalong
                uint32 amount;                                  // datalong2
            } removeItem;

                                                                // SCRIPT_COMMAND_REMOVE_OBJECT (41)

            struct                                              // SCRIPT_COMMAND_SET_MELEE_ATTACK (42)
            {
                uint32 enabled;                                 // datalong
            } enableMelee;

            struct                                              // SCRIPT_COMMAND_SET_COMBAT_MOVEMENT (43)
            {
                uint32 enabled;                                 // datalong
            } combatMovement;

            struct                                              // SCRIPT_COMMAND_SET_PHASE (44)
            {
                uint32 phase;                                   // datalong
                uint32 mode;                                    // datalong2
            } setPhase;

            struct                                              // SCRIPT_COMMAND_SET_PHASE_RANDOM (45)
            {
                uint32 phase[MAX_TEXT_ID];                      // datalong
            } setPhaseRandom;

            struct                                              // SCRIPT_COMMAND_SET_PHASE_RANGE (46)
            {
                uint32 phaseMin;                                // datalong
                uint32 phaseMax;                                // datalong2
            } setPhaseRange;

            struct                                              // SCRIPT_COMMAND_FLEE (47)
            {
                uint32 seekAssistance;                          // datalong
            } flee;

            struct                                              // SCRIPT_COMMAND_DEAL_DAMAGE (48)
            {
                uint32 damage;                                  // datalong
                uint32 isPercent;                               // datalong2
            } dealDamage;

            struct                                              // SCRIPT_COMMAND_ZONE_COMBAT_PULSE (49)
            {
                uint32 initialPulse;                            // datalong
            } combatPulse;

                                                                // SCRIPT_COMMAND_CALL_FOR_HELP (50)

            struct                                              // SCRIPT_COMMAND_SET_SHEATH (51)
            {
                uint32 sheathState;                             // datalong
            } setSheath;

            struct                                              // SCRIPT_COMMAND_INVINCIBILITY (52)
            {
                uint32 health;                                  // datalong
                uint32 isPercent;                               // datalong2
            } invincibility;

            struct                                              // SCRIPT_COMMAND_GAME_EVENT (53)
            {
                uint32 eventId;                                 // datalong
                uint32 start;                                   // datalong2
                uint32 overwrite;                               // datalong3
            } gameEvent;

            struct                                              // SCRIPT_COMMAND_SET_SERVER_VARIABLE (54)
            {
                uint32 index;                                   // datalong
                uint32 value;                                   // datalong2
            } serverVariable;

            struct                                              // SCRIPT_COMMAND_CREATURE_SPELLS (55)
            {
                uint32 spellTemplate[4];                        // datalong to datalong4
                uint32 unused;                                  // data_flags
                int32 chance[4];                                // dataint to dataint4
            } creatureSpells;

            struct                                              // SCRIPT_COMMAND_REMOVE_GUARDIANS (56)
            {
                uint32 creatureId;                              // datalong
            } removeGuardian;

            struct                                              // SCRIPT_COMMAND_ADD_SPELL_COOLDOWN (57)
            {
                uint32 spellId;                                 // datalong
                uint32 cooldown;                                // datalong2
            } addCooldown;

            struct                                              // SCRIPT_COMMAND_REMOVE_SPELL_COOLDOWN (58)
            {
                uint32 spellId;                                 // datalong
            } removeCooldown;

            struct                                              // SCRIPT_COMMAND_SET_REACT_STATE (59)
            {
                uint32 state;                                   // datalong
            } setReactState;

            struct                                              // SCRIPT_COMMAND_START_WAYPOINTS (60)
            {
                uint32 wpSource;                                // datalong
                uint32 startPoint;                              // datalong2
                uint32 initialDelay;                            // datalong3
                uint32 canRepeat;                               // datalong4
                uint32 unused;                                  // data_flags
                int32  pathId;                                  // dataint
                int32  overwriteEntry;                          // dataint2
            } startWaypoints;
        
            struct                                              // SCRIPT_COMMAND_START_MAP_EVENT (61)
            {
                uint32 eventId;                                 // datalong
                uint32 timeLimit;                               // datalong2
                uint32 unused1;                                 // datalong3
                uint32 unuded2;                                 // datalong4
                uint32 unused3;                                 // data_flags
                int32  successCondition;                        // dataint
                int32  successScript;                           // dataint2
                int32  failureCondition;                        // dataint3
                int32  failureScript;                           // dataint4
            } startMapEvent;

            struct                                              // SCRIPT_COMMAND_END_MAP_EVENT (62)
            {
                uint32 eventId;                                 // datalong
                uint32 success;                                 // datalong2
            } endMapEvent;

            struct                                              // SCRIPT_COMMAND_ADD_MAP_EVENT_TARGET (63)
            {
                uint32 eventId;                                 // datalong
                uint32 unused1;                                 // datalong2
                uint32 unused2;                                 // datalong3
                uint32 unused3;                                 // datalong4
                uint32 unused4;                                 // data_flags
                int32  successCondition;                        // dataint
                int32  successScript;                           // dataint2
                int32  failureCondition;                        // dataint3
                int32  failureScript;                           // dataint4
            } addMapEventTarget;

            struct                                              // SCRIPT_COMMAND_REMOVE_MAP_EVENT_TARGET (64)
            {
                uint32 eventId;                                 // datalong
                uint32 conditionId;                             // datalong2
                uint32 targets;                                 // datalong3
            } removeMapEventTarget;

            struct                                              // SCRIPT_COMMAND_SET_MAP_EVENT_DATA (65)
            {
                uint32 eventId;                                 // datalong
                uint32 index;                                   // datalong2
                uint32 data;                                    // datalong3
                uint32 type;                                    // datalong4
            } setMapEventData;

            struct                                              // SCRIPT_COMMAND_SEND_MAP_EVENT (66)
            {
                uint32 eventId;                                 // datalong
                uint32 data;                                    // datalong2
                uint32 targets;                                 // datalong3
            } sendMapEvent;

            struct                                              // SCRIPT_COMMAND_SET_DEFAULT_MOVEMENT (67)
            {
                uint32 movementType;                            // datalong
                uint32 alwaysReplace;                           // datalong2
                uint32 param1;                                  // datalong3
            } setDefaultMovement;

            struct                                              // SCRIPT_COMMAND_START_SCRIPT_FOR_ALL (68)
            {
                uint32 scriptId;                                // datalong
                uint32 objectType;                              // datalong2
                uint32 objectEntry;                             // datalong3
                uint32 searchRadius;                            // datalong4
            } startScriptForAll;

            struct                                              // SCRIPT_COMMAND_EDIT_MAP_EVENT (69)
            {
                uint32 eventId;                                 // datalong
                uint32 unused1;                                 // datalong2
                uint32 unused2;                                 // datalong3
                uint32 unused3;                                 // datalong4
                uint32 unused4;                                 // data_flags
                int32  successCondition;                        // dataint
                int32  successScript;                           // dataint2
                int32  failureCondition;                        // dataint3
                int32  failureScript;                           // dataint4
            } editMapEvent;

            struct                                              // SCRIPT_COMMAND_FAIL_QUEST (70)
            {
                uint32 questId;                                 // datalong
            } failQuest;

            struct                                              // SCRIPT_COMMAND_RESPAWN_CREATURE (71)
            {
                uint32 evenAlive;                               // datalong
            } respawnCreature;

                                                                // SCRIPT_COMMAND_ASSIST_UNIT (72)

                                                                // SCRIPT_COMMAND_COMBAT_STOP (73)

            struct                                              // SCRIPT_COMMAND_ADD_AURA (74)
            {
                uint32 spellId;                                 // datalong
                uint32 flags;                                   // datalong2
            } addAura;

                                                                // SCRIPT_COMMAND_ADD_THREAT (75)
            struct
            {
                uint32 data[9];
            } raw;
        };

        uint32 target_param1;
        uint32 target_param2;
        uint32 target_type;

        float x;
        float y;
        float z;
        float o;

        std::string comment;

        ScriptInfo() : id(0), delay(0), command(0), condition(0), target_param1(0), target_param2(0), target_type(0), x(0), y(0), z(0), o(0), comment("")
        {
            memset(raw.data, 0, sizeof(raw.data));
        }

        // helpers
        uint32 GetGOGuid() const
        {
            switch(command)
            {
                case SCRIPT_COMMAND_RESPAWN_GAMEOBJECT: return respawnGo.goGuid;
                case SCRIPT_COMMAND_OPEN_DOOR: return openDoor.goGuid;
                case SCRIPT_COMMAND_CLOSE_DOOR: return closeDoor.goGuid;
                default: return 0;
            }
        }
    };

    enum CastFlags
    {
        CF_INTERRUPT_PREVIOUS     = 0x01,                     //Interrupt any spell casting
        CF_TRIGGERED              = 0x02,                     //Triggered (this makes spell cost zero mana and have no cast time)
        CF_FORCE_CAST             = 0x04,                     //Forces cast even if creature is out of mana or out of range
        CF_MAIN_RANGED_SPELL      = 0x08,                     //To be used by ranged mobs only. Creature will not chase target until cast fails.
        CF_TARGET_UNREACHABLE     = 0x10,                     //Will only use the ability if creature cannot currently get to target
        CF_AURA_NOT_PRESENT       = 0x20,                     //Only casts the spell if the target does not have an aura from the spell
        CF_ONLY_IN_MELEE          = 0x40,                     //Only casts if the creature is in melee range of the target
        CF_NOT_IN_MELEE           = 0x80,                     //Only casts if the creature is not in melee range of the target
    };

    // Values used in target_type column
    enum ScriptTarget
    {
        TARGET_T_PROVIDED_TARGET                = 0,            //Object that was provided to the command.

        TARGET_T_HOSTILE                        = 1,            //Our current target (ie: highest aggro).
        TARGET_T_HOSTILE_SECOND_AGGRO           = 2,            //Second highest aggro (generaly used for cleaves and some special attacks).
        TARGET_T_HOSTILE_LAST_AGGRO             = 3,            //Dead last on aggro (no idea what this could be used for).
        TARGET_T_HOSTILE_RANDOM                 = 4,            //Just any random target on our threat list.
        TARGET_T_HOSTILE_RANDOM_NOT_TOP         = 5,            //Any random target except top threat.

        TARGET_T_OWNER_OR_SELF                  = 6,            //Either self or owner if pet or controlled.
        TARGET_T_OWNER                          = 7,            //The owner of the source.
    

        TARGET_T_CREATURE_WITH_ENTRY            = 8,            //Searches for nearby creature with the given entry.
                                                                //Param1 = creature_entry
                                                                //Param2 = search_radius

        TARGET_T_CREATURE_WITH_GUID             = 9,            //The creature with this database guid.
                                                                //Param1 = db_guid

        TARGET_T_CREATURE_FROM_INSTANCE_DATA    = 10,           //Find creature by guid stored in instance data.
                                                                //Param1 = instance_data_field

        TARGET_T_GAMEOBJECT_WITH_ENTRY          = 11,           //Searches for nearby gameobject with the given entry.
                                                                //Param1 = gameobject_entry
                                                                //Param2 = search_radius

        TARGET_T_GAMEOBJECT_WITH_GUID           = 12,           //The gameobject with this database guid.
                                                                //Param1 = db_guid

        TARGET_T_GAMEOBJECT_FROM_INSTANCE_DATA  = 13,           //Find gameobject by guid stored in instance data.
                                                                //Param1 = instance_data_field

        TARGET_T_FRIENDLY                       = 14,           //Random friendly unit.
                                                                //Param1 = search_radius
                                                                //Param2 = (bool) exclude_target
        TARGET_T_FRIENDLY_INJURED               = 15,           //Friendly unit missing the most health.
                                                                //Param1 = search_radius
                                                                //Param2 = hp_percent
        TARGET_T_FRIENDLY_INJURED_EXCEPT        = 16,           //Friendly unit missing the most health but not provided target.
                                                                //Param1 = search_radius
                                                                //Param2 = hp_percent
        TARGET_T_FRIENDLY_MISSING_BUFF          = 17,           //Friendly unit without aura.
                                                                //Param1 = search_radius
                                                                //Param2 = spell_id
        TARGET_T_FRIENDLY_MISSING_BUFF_EXCEPT   = 18,           //Friendly unit without aura but not provided target.
                                                                //Param1 = search_radius
                                                                //Param2 = spell_id
        TARGET_T_FRIENDLY_CC                    = 19,           //Friendly unit under crowd control.
                                                                //Param1 = search_radius
        TARGET_T_MAP_EVENT_SOURCE               = 20,           //The source WorldObject of a scripted map event.
                                                                //Param1 = eventId
        TARGET_T_MAP_EVENT_TARGET               = 21,           //The target WorldObject of a scripted map event.
                                                                //Param1 = eventId
        TARGET_T_MAP_EVENT_EXTRA_TARGET         = 22,           //An additional WorldObject target from a scripted map event.
                                                                //Param1 = eventId
                                                                //Param2 = creature_entry or gameobject_entry
        TARGET_T_END
    };

    enum TempSummonType
    {
        TEMPSUMMON_TIMED_OR_DEAD_DESPAWN          = 1,             // despawns after a specified time (out of combat) OR when the creature disappears
        TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN        = 2,             // despawns after a specified time (out of combat) OR when the creature dies
        TEMPSUMMON_TIMED_DESPAWN                  = 3,             // despawns after a specified time
        TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT    = 4,             // despawns after a specified time after the creature is out of combat
        TEMPSUMMON_CORPSE_DESPAWN                 = 5,             // despawns instantly after death
        TEMPSUMMON_CORPSE_TIMED_DESPAWN           = 6,             // despawns after a specified time after death
        TEMPSUMMON_DEAD_DESPAWN                   = 7,             // despawns when the creature disappears
        TEMPSUMMON_MANUAL_DESPAWN                 = 8,             // despawns when UnSummon() is called
        TEMPSUMMON_TIMED_COMBAT_OR_DEAD_DESPAWN   = 9,             // despawns after a specified time (in or out of combat) OR when the creature disappears
        TEMPSUMMON_TIMED_COMBAT_OR_CORPSE_DESPAWN = 10,            // despawns after a specified time (in or out of combat) OR when the creature dies

    };

    // values 0 ... MAX_DB_MOTION_TYPE-1 used in DB
    enum MovementGeneratorType
    {
        IDLE_MOTION_TYPE                = 0,                    // IdleMovementGenerator.h
        RANDOM_MOTION_TYPE              = 1,                    // RandomMovementGenerator.h
        WAYPOINT_MOTION_TYPE            = 2,                    // WaypointMovementGenerator.h
        MAX_DB_MOTION_TYPE              = 3,                    // *** this and below motion types can't be set in DB.

        CONFUSED_MOTION_TYPE            = 4,                    // ConfusedMovementGenerator.h
        CHASE_MOTION_TYPE               = 5,                    // TargetedMovementGenerator.h
        HOME_MOTION_TYPE                = 6,                    // HomeMovementGenerator.h
        FLIGHT_MOTION_TYPE              = 7,                    // WaypointMovementGenerator.h
        POINT_MOTION_TYPE               = 8,                    // PointMovementGenerator.h
        FLEEING_MOTION_TYPE             = 9,                    // FleeingMovementGenerator.h
        DISTRACT_MOTION_TYPE            = 10,                   // IdleMovementGenerator.h
        ASSISTANCE_MOTION_TYPE          = 11,                   // PointMovementGenerator.h (first part of flee for assistance)
        ASSISTANCE_DISTRACT_MOTION_TYPE = 12,                   // IdleMovementGenerator.h (second part of flee for assistance)
        TIMED_FLEEING_MOTION_TYPE       = 13,                   // FleeingMovementGenerator.h (alt.second part of flee for assistance)
        FOLLOW_MOTION_TYPE              = 14,                   // TargetedMovementGenerator.h
        EFFECT_MOTION_TYPE              = 15,
        PATROL_MOTION_TYPE              = 16,
        CHARGE_MOTION_TYPE              = 17,

        WAYPOINT_SPECIAL_REACHED        = 256,                  // Only used in CreatureAI::MovementInform when a special waypoint is reached. The pathId >= 0 is added as additonal value
        WAYPOINT_SPECIAL_STARTED        = 512,                  // Only used in CreatureAI::MovementInform when a special waypoint is started. The pathId >= 0 is added as additional value
        WAYPOINT_SPECIAL_FINISHED_LAST  = 1024,                 // Only used in CreatureAI::MovementInform when the waittime of the last special wp is finished. The pathId >= 0 is added as additional value
    };
}
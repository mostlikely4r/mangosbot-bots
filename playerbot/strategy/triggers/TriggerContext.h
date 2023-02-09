#pragma once

#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "LootTriggers.h"
#include "GenericTriggers.h"
#include "LfgTriggers.h"
#include "PvpTriggers.h"
#include "RpgTriggers.h"
#include "TravelTriggers.h"
#include "RtiTriggers.h"
#include "CureTriggers.h"
#include "GuildTriggers.h"
#include "StuckTriggers.h"
#include "BotStateTriggers.h"
#include "PullTriggers.h"
#include "OnyxiasLairDungeonTriggers.h"
#include "MoltenCoreDungeonTriggers.h"

namespace ai
{
    class TriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        TriggerContext()
        {
            creators["return"] = &TriggerContext::_return;
            creators["sit"] = &TriggerContext::sit;
            creators["return to stay position"] = &TriggerContext::return_to_stay_position;
            creators["return to pull position"] = &TriggerContext::return_to_pull_position;
            creators["collision"] = &TriggerContext::collision;

            creators["timer"] = &TriggerContext::Timer;
            creators["random"] = &TriggerContext::Random;
            creators["seldom"] = &TriggerContext::seldom;
            creators["often"] = &TriggerContext::often;
            creators["very often"] = &TriggerContext::very_often;

            creators["target critical health"] = &TriggerContext::TargetCriticalHealth;

            creators["critical health"] = &TriggerContext::CriticalHealth;
            creators["low health"] = &TriggerContext::LowHealth;
            creators["medium health"] = &TriggerContext::MediumHealth;
            creators["almost full health"] = &TriggerContext::AlmostFullHealth;

            creators["low mana"] = &TriggerContext::LowMana;
            creators["medium mana"] = &TriggerContext::MediumMana;
            creators["high mana"] = &TriggerContext::HighMana;
            creators["almost full mana"] = &TriggerContext::AlmostFullMana;

            creators["party member critical health"] = &TriggerContext::PartyMemberCriticalHealth;
            creators["party member low health"] = &TriggerContext::PartyMemberLowHealth;
            creators["party member medium health"] = &TriggerContext::PartyMemberMediumHealth;
            creators["party member almost full health"] = &TriggerContext::PartyMemberAlmostFullHealth;

            creators["protect party member"] = &TriggerContext::protect_party_member;

            creators["light rage available"] = &TriggerContext::LightRageAvailable;
            creators["medium rage available"] = &TriggerContext::MediumRageAvailable;
            creators["high rage available"] = &TriggerContext::HighRageAvailable;

            creators["light energy available"] = &TriggerContext::LightEnergyAvailable;
            creators["medium energy available"] = &TriggerContext::MediumEnergyAvailable;
            creators["high energy available"] = &TriggerContext::HighEnergyAvailable;

            creators["loot available"] = &TriggerContext::LootAvailable;
            creators["no attackers"] = &TriggerContext::NoAttackers;
            creators["no target"] = &TriggerContext::NoTarget;
            creators["target in sight"] = &TriggerContext::TargetInSight;
            creators["not dps target active"] = &TriggerContext::not_dps_target_active;
            creators["not dps aoe target active"] = &TriggerContext::not_dps_aoe_target_active;
            creators["has nearest adds"] = &TriggerContext::has_nearest_adds;
            creators["enemy player near"] = &TriggerContext::enemy_player_near;
            
            creators["combat start"] = &TriggerContext::combat_start;
            creators["combat end"] = &TriggerContext::combat_end;
            creators["death"] = &TriggerContext::death;
            creators["resurrect"] = &TriggerContext::resurrect;

            creators["pull start"] = &TriggerContext::pull_start;
            creators["pull end"] = &TriggerContext::pull_end;

            creators["tank assist"] = &TriggerContext::TankAssist;
            creators["lose aggro"] = &TriggerContext::LoseAggro;
            creators["has aggro"] = &TriggerContext::HasAggro;

            creators["light aoe"] = &TriggerContext::LightAoe;
            creators["medium aoe"] = &TriggerContext::MediumAoe;
            creators["high aoe"] = &TriggerContext::HighAoe;

            creators["has area debuff"] = &TriggerContext::HasAreaDebuff;

            creators["enemy out of melee"] = &TriggerContext::EnemyOutOfMelee;
            creators["enemy out of spell"] = &TriggerContext::EnemyOutOfSpell;
            creators["enemy too close for spell"] = &TriggerContext::enemy_too_close_for_spell;
            creators["enemy too close for shoot"] = &TriggerContext::enemy_too_close_for_shoot;
            creators["enemy too close for melee"] = &TriggerContext::enemy_too_close_for_melee;
            creators["enemy is close"] = &TriggerContext::enemy_is_close;
            creators["party member to heal out of spell range"] = &TriggerContext::party_member_to_heal_out_of_spell_range;
            creators["enemy fifteen yards"] = &TriggerContext::enemy_fifteen_yards;
            creators["enemy ten yards"] = &TriggerContext::enemy_ten_yards;
            creators["enemy five yards"] = &TriggerContext::enemy_five_yards;
            creators["wait for attack safe distance"] = &TriggerContext::wait_for_attack_safe_distance;

            creators["combo points available"] = &TriggerContext::ComboPointsAvailable;

            creators["medium threat"] = &TriggerContext::MediumThreat;

            creators["dead"] = &TriggerContext::Dead;
            creators["corpse near"] = &TriggerContext::corpse_near;
            creators["party member dead"] = &TriggerContext::PartyMemberDead;
            creators["no pet"] = &TriggerContext::no_pet;
            creators["has attackers"] = &TriggerContext::has_attackers;
            creators["no possible targets"] = &TriggerContext::no_possible_targets;
            creators["possible adds"] = &TriggerContext::possible_adds;

            creators["no drink"] = &TriggerContext::no_drink;
            creators["no food"] = &TriggerContext::no_food;

            creators["panic"] = &TriggerContext::panic;
            creators["outnumbered"] = &TriggerContext::outnumbered;
            creators["behind target"] = &TriggerContext::behind_target;
            creators["not behind target"] = &TriggerContext::not_behind_target;
            creators["not facing target"] = &TriggerContext::not_facing_target;
            creators["far from master"] = &TriggerContext::far_from_master;
            creators["not near master"] = &TriggerContext::not_near_master;
            creators["update follow"] = &TriggerContext::update_follow;
            creators["stop follow"] = &TriggerContext::stop_follow;
            creators["far from loot target"] = &TriggerContext::far_from_loot_target;
            creators["can loot"] = &TriggerContext::can_loot;
            creators["swimming"] = &TriggerContext::swimming;
            creators["target changed"] = &TriggerContext::target_changed;

            creators["critical aoe heal"] = &TriggerContext::critical_aoe_heal;
            creators["low aoe heal"] = &TriggerContext::low_aoe_heal;
            creators["medium aoe heal"] = &TriggerContext::medium_aoe_heal;
            creators["invalid target"] = &TriggerContext::invalid_target;
            creators["lfg proposal active"] = &TriggerContext::lfg_proposal_active;

            creators["unknown dungeon"] = &TriggerContext::unknown_dungeon;

            creators["random bot update"] = &TriggerContext::random_bot_update_trigger;
            creators["no non bot players around"] = &TriggerContext::no_non_bot_players_around;
            creators["new player nearby"] = &TriggerContext::new_player_nearby;
            creators["no rpg target"] = &TriggerContext::no_rpg_target;
            creators["has rpg target"] = &TriggerContext::has_rpg_target;
            creators["far from rpg target"] = &TriggerContext::far_from_rpg_target;
            creators["near rpg target"] = &TriggerContext::near_rpg_target;
            creators["no travel target"] = &TriggerContext::no_travel_target;
            creators["far from travel target"] = &TriggerContext::far_from_travel_target;			
            creators["no rti target"] = &TriggerContext::no_rti;

            creators["give food"] = &TriggerContext::give_food;
            creators["give water"] = &TriggerContext::give_water;

            creators["bg waiting"] = &TriggerContext::bg_waiting;
            creators["bg active"] = &TriggerContext::bg_active;
            creators["bg invite active"] = &TriggerContext::bg_invite_active;
            creators["player has no flag"] = &TriggerContext::player_has_no_flag;
            creators["player has flag"] = &TriggerContext::player_has_flag;
            creators["team has flag"] = &TriggerContext::team_has_flag;
            creators["enemy team has flag"] = &TriggerContext::enemy_team_has_flag;
            creators["enemy flagcarrier near"] = &TriggerContext::enemy_flagcarrier_near;
            creators["in battleground"] = &TriggerContext::player_is_in_battleground;
            creators["in battleground without flag"] = &TriggerContext::player_is_in_battleground_no_flag;
            creators["wants in bg"] = &TriggerContext::player_wants_in_bg;
            creators["use trinket"] = &TriggerContext::use_trinket;

            creators["mounted"] = &TriggerContext::mounted;

            // move to/enter dark portal if near
            creators["near dark portal"] = &TriggerContext::near_dark_portal;
            creators["at dark portal azeroth"] = &TriggerContext::at_dark_portal_azeroth;
            creators["at dark portal outland"] = &TriggerContext::at_dark_portal_outland;

            creators["vehicle near"] = &TriggerContext::vehicle_near;
            creators["in vehicle"] = &TriggerContext::in_vehicle;

            creators["need world buff"] = &TriggerContext::need_world_buff;
            creators["falling"] = &TriggerContext::falling;
            creators["falling far"] = &TriggerContext::falling_far;
            creators["move stuck"] = &TriggerContext::move_stuck;
            creators["move long stuck"] = &TriggerContext::move_long_stuck;
            creators["combat stuck"] = &TriggerContext::combat_stuck;
            creators["combat long stuck"] = &TriggerContext::combat_long_stuck;
            creators["leader is afk"] = &TriggerContext::leader_is_afk;

            creators["petition signed"] = &TriggerContext::petition_signed;
            creators["buy tabard"] = &TriggerContext::buy_tabard;
            creators["leave large guild"] = &TriggerContext::leave_large_guild;

            creators["val"] = &TriggerContext::val;

            creators["rpg"] = &TriggerContext::rpg;
            creators["rpg wander"] = &TriggerContext::rpg_wander;
            creators["rpg taxi"] = &TriggerContext::rpg_taxi;
            creators["rpg discover"] = &TriggerContext::rpg_discover;
            creators["rpg start quest"] = &TriggerContext::rpg_start_quest;
            creators["rpg end quest"] = &TriggerContext::rpg_end_quest;
            creators["rpg repeat quest"] = &TriggerContext::rpg_repeat_quest;
            creators["rpg buy"] = &TriggerContext::rpg_buy;
            creators["rpg sell"] = &TriggerContext::rpg_sell;
            creators["rpg ah sell"] = &TriggerContext::rpg_ah_sell;
            creators["rpg ah buy"] = &TriggerContext::rpg_ah_buy;
            creators["rpg get mail"] = &TriggerContext::rpg_get_mail;
            creators["rpg repair"] = &TriggerContext::rpg_repair;
            creators["rpg train"] = &TriggerContext::rpg_train;
            creators["rpg heal"] = &TriggerContext::rpg_heal;
            creators["rpg home bind"] = &TriggerContext::rpg_home_bind;
            creators["rpg queue bg"] = &TriggerContext::rpg_queue_bg;
            creators["rpg buy petition"] = &TriggerContext::rpg_buy_petition;
            creators["rpg use"] = &TriggerContext::rpg_use;
            creators["rpg spell"] = &TriggerContext::rpg_spell;
            creators["rpg craft"] = &TriggerContext::rpg_craft;
            creators["rpg trade useful"] = &TriggerContext::rpg_trade_useful;
            creators["rpg duel"] = &TriggerContext::rpg_duel;

            // racials
            creators["berserking"] = &TriggerContext::berserking;
            creators["blood fury"] = &TriggerContext::blood_fury;
            creators["cannibalize"] = &TriggerContext::cannibalize;
            creators["will of the forsaken"] = &TriggerContext::will_of_the_forsaken;
            creators["rooted"] = &TriggerContext::rooted;
            creators["stoneform"] = &TriggerContext::stoneform;
            creators["shadowmeld"] = &TriggerContext::shadowmeld;
            creators["mana tap"] = &TriggerContext::mana_tap;
            creators["arcane torrent"] = &TriggerContext::arcane_torrent;
            creators["war stomp"] = &TriggerContext::war_stomp;
            creators["perception"] = &TriggerContext::cannibalize;

            // Dungeon Triggers
            creators["enter onyxia's lair"] = &TriggerContext::onyxias_lair_enter;
            creators["leave onyxia's lair"] = &TriggerContext::onyxias_lair_leave;
            creators["enter molten core"] = &TriggerContext::molten_core_enter;
            creators["leave molten core"] = &TriggerContext::molten_core_leave;

            // Dungeon Boss Triggers
            creators["start onyxia fight"] = &TriggerContext::onyxia_start_fight;
            creators["end onyxia fight"] = &TriggerContext::onyxia_end_fight;

            creators["start magmadar fight"] = &TriggerContext::magmadar_start_fight;
            creators["end magmadar fight"] = &TriggerContext::magmadar_end_fight;
            creators["magmadar lava bomb"] = &TriggerContext::magmadar_lava_bomb;

            creators["mc rune in sight"] = &TriggerContext::mc_rune_in_sight;
            creators["mc rune close"] = &TriggerContext::mc_rune_close;
        }

    private:
        static Trigger* berserking(PlayerbotAI* ai) { return new BerserkingTrigger(ai); }
        static Trigger* blood_fury(PlayerbotAI* ai) { return new BloodFuryTrigger(ai); }
        static Trigger* cannibalize(PlayerbotAI* ai) { return new CannibalizeTrigger(ai); }
        static Trigger* will_of_the_forsaken(PlayerbotAI* ai) { return new WOtFTrigger(ai); }
        static Trigger* rooted(PlayerbotAI* ai) { return new RootedTrigger(ai); }
        static Trigger* stoneform(PlayerbotAI* ai) { return new StoneformTrigger(ai); }
        static Trigger* shadowmeld(PlayerbotAI* ai) { return new ShadowmeldTrigger(ai); }
        static Trigger* mana_tap(PlayerbotAI* ai) { return new ManaTapTrigger(ai); }
        static Trigger* arcane_torrent(PlayerbotAI* ai) { return new ArcanetorrentTrigger(ai); }
        static Trigger* war_stomp(PlayerbotAI* ai) { return new WarStompTrigger(ai); }
        static Trigger* perception(PlayerbotAI* ai) { return new PerceptionTrigger(ai); }
        static Trigger* in_vehicle(PlayerbotAI* ai) { return new InVehicleTrigger(ai); }
        static Trigger* vehicle_near(PlayerbotAI* ai) { return new VehicleNearTrigger(ai); }
        static Trigger* at_dark_portal_outland(PlayerbotAI* ai) { return new AtDarkPortalOutlandTrigger(ai); }
        static Trigger* at_dark_portal_azeroth(PlayerbotAI* ai) { return new AtDarkPortalAzerothTrigger(ai); }
        static Trigger* near_dark_portal(PlayerbotAI* ai) { return new NearDarkPortalTrigger(ai); }
        static Trigger* mounted(PlayerbotAI* ai) { return new IsMountedTrigger(ai); }
        static Trigger* enemy_flagcarrier_near(PlayerbotAI* ai) { return new EnemyFlagCarrierNear(ai); }
        static Trigger* player_has_no_flag(PlayerbotAI* ai) { return new PlayerHasNoFlag(ai); }
        static Trigger* bg_waiting(PlayerbotAI* ai) { return new BgWaitingTrigger(ai); }
        static Trigger* bg_active(PlayerbotAI* ai) { return new BgActiveTrigger(ai); }
        static Trigger* bg_invite_active(PlayerbotAI* ai) { return new BgInviteActiveTrigger(ai); }
        static Trigger* player_has_flag(PlayerbotAI* ai) { return new PlayerHasFlag(ai); }
        static Trigger* team_has_flag(PlayerbotAI* ai) { return new TeamHasFlag(ai); }
        static Trigger* enemy_team_has_flag(PlayerbotAI* ai) { return new EnemyTeamHasFlag(ai); }
        static Trigger* player_is_in_battleground(PlayerbotAI *ai) { return new PlayerIsInBattleground(ai); }
        static Trigger* player_is_in_battleground_no_flag(PlayerbotAI *ai) { return new PlayerIsInBattlegroundWithoutFlag(ai); }
        static Trigger* give_food(PlayerbotAI* ai) { return new GiveFoodTrigger(ai); }
        static Trigger* give_water(PlayerbotAI* ai) { return new GiveWaterTrigger(ai); }
        static Trigger* no_rti(PlayerbotAI* ai) { return new NoRtiTrigger(ai); }
        static Trigger* _return(PlayerbotAI* ai) { return new ReturnTrigger(ai); }
        static Trigger* return_to_stay_position(PlayerbotAI* ai) { return new ReturnToStayPositionTrigger(ai); }
        static Trigger* return_to_pull_position(PlayerbotAI* ai) { return new ReturnToPullPositionTrigger(ai); }
        static Trigger* sit(PlayerbotAI* ai) { return new SitTrigger(ai); }
        static Trigger* far_from_rpg_target(PlayerbotAI* ai) { return new FarFromRpgTargetTrigger(ai); }
        static Trigger* near_rpg_target(PlayerbotAI* ai) { return new NearRpgTargetTrigger(ai); }
        static Trigger* no_rpg_target(PlayerbotAI* ai) { return new NoRpgTargetTrigger(ai); }
        static Trigger* has_rpg_target(PlayerbotAI* ai) { return new HasRpgTargetTrigger(ai); }
        static Trigger* far_from_travel_target(PlayerbotAI* ai) { return new FarFromTravelTargetTrigger(ai); }
        static Trigger* no_travel_target(PlayerbotAI* ai) { return new NoTravelTargetTrigger(ai); }		
        static Trigger* collision(PlayerbotAI* ai) { return new CollisionTrigger(ai); }
        static Trigger* lfg_proposal_active(PlayerbotAI* ai) { return new LfgProposalActiveTrigger(ai); }
        static Trigger* unknown_dungeon(PlayerbotAI* ai) { return new UnknownDungeonTrigger(ai); }
        static Trigger* invalid_target(PlayerbotAI* ai) { return new InvalidTargetTrigger(ai); }
        static Trigger* critical_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "critical aoe heal", "critical", 2); }
        static Trigger* low_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "low aoe heal", "low", 2); }
        static Trigger* medium_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "medium aoe heal", "medium", 2); }
        static Trigger* target_changed(PlayerbotAI* ai) { return new TargetChangedTrigger(ai); }
        static Trigger* swimming(PlayerbotAI* ai) { return new IsSwimmingTrigger(ai); }
        static Trigger* no_possible_targets(PlayerbotAI* ai) { return new NoPossibleTargetsTrigger(ai); }
        static Trigger* possible_adds(PlayerbotAI* ai) { return new PossibleAddsTrigger(ai); }
        static Trigger* can_loot(PlayerbotAI* ai) { return new CanLootTrigger(ai); }
        static Trigger* far_from_loot_target(PlayerbotAI* ai) { return new FarFromCurrentLootTrigger(ai); }
        static Trigger* far_from_master(PlayerbotAI* ai) { return new FarFromMasterTrigger(ai); }
        static Trigger* not_near_master(PlayerbotAI* ai) { return new NotNearMasterTrigger(ai); }
        static Trigger* update_follow(PlayerbotAI* ai) { return new UpdateFollowTrigger(ai); }
        static Trigger* stop_follow(PlayerbotAI* ai) { return new StopFollowTrigger(ai); }
        static Trigger* behind_target(PlayerbotAI* ai) { return new IsBehindTargetTrigger(ai); }
        static Trigger* not_behind_target(PlayerbotAI* ai) { return new IsNotBehindTargetTrigger(ai); }
        static Trigger* not_facing_target(PlayerbotAI* ai) { return new IsNotFacingTargetTrigger(ai); }
        static Trigger* panic(PlayerbotAI* ai) { return new PanicTrigger(ai); }
        static Trigger* outnumbered(PlayerbotAI* ai) { return new OutNumberedTrigger(ai); }
        static Trigger* no_drink(PlayerbotAI* ai) { return new NoDrinkTrigger(ai); }
        static Trigger* no_food(PlayerbotAI* ai) { return new NoFoodTrigger(ai); }
        static Trigger* LightAoe(PlayerbotAI* ai) { return new LightAoeTrigger(ai); }
        static Trigger* MediumAoe(PlayerbotAI* ai) { return new MediumAoeTrigger(ai); }
        static Trigger* HighAoe(PlayerbotAI* ai) { return new HighAoeTrigger(ai); }
        static Trigger* HasAreaDebuff(PlayerbotAI* ai) { return new HasAreaDebuffTrigger(ai); }
        static Trigger* LoseAggro(PlayerbotAI* ai) { return new LoseAggroTrigger(ai); }
        static Trigger* HasAggro(PlayerbotAI* ai) { return new HasAggroTrigger(ai); }
        static Trigger* LowHealth(PlayerbotAI* ai) { return new LowHealthTrigger(ai); }
        static Trigger* MediumHealth(PlayerbotAI* ai) { return new MediumHealthTrigger(ai); }
        static Trigger* AlmostFullHealth(PlayerbotAI* ai) { return new AlmostFullHealthTrigger(ai); }
        static Trigger* CriticalHealth(PlayerbotAI* ai) { return new CriticalHealthTrigger(ai); }
        static Trigger* TargetCriticalHealth(PlayerbotAI* ai) { return new TargetCriticalHealthTrigger(ai); }
        static Trigger* LowMana(PlayerbotAI* ai) { return new LowManaTrigger(ai); }
        static Trigger* MediumMana(PlayerbotAI* ai) { return new MediumManaTrigger(ai); }
        static Trigger* HighMana(PlayerbotAI* ai) { return new HighManaTrigger(ai); }
        static Trigger* AlmostFullMana(PlayerbotAI* ai) { return new AlmostFullManaTrigger(ai); }
        static Trigger* LightRageAvailable(PlayerbotAI* ai) { return new LightRageAvailableTrigger(ai); }
        static Trigger* MediumRageAvailable(PlayerbotAI* ai) { return new MediumRageAvailableTrigger(ai); }
        static Trigger* HighRageAvailable(PlayerbotAI* ai) { return new HighRageAvailableTrigger(ai); }
        static Trigger* LightEnergyAvailable(PlayerbotAI* ai) { return new LightEnergyAvailableTrigger(ai); }
        static Trigger* MediumEnergyAvailable(PlayerbotAI* ai) { return new MediumEnergyAvailableTrigger(ai); }
        static Trigger* HighEnergyAvailable(PlayerbotAI* ai) { return new HighEnergyAvailableTrigger(ai); }
        static Trigger* LootAvailable(PlayerbotAI* ai) { return new LootAvailableTrigger(ai); }
        static Trigger* NoAttackers(PlayerbotAI* ai) { return new NoAttackersTrigger(ai); }
        static Trigger* TankAssist(PlayerbotAI* ai) { return new TankAssistTrigger(ai); }
        static Trigger* Timer(PlayerbotAI* ai) { return new TimerTrigger(ai); }
        static Trigger* NoTarget(PlayerbotAI* ai) { return new NoTargetTrigger(ai); }
        static Trigger* TargetInSight(PlayerbotAI* ai) { return new TargetInSightTrigger(ai); }
        static Trigger* not_dps_target_active(PlayerbotAI* ai) { return new NotDpsTargetActiveTrigger(ai); }
        static Trigger* not_dps_aoe_target_active(PlayerbotAI* ai) { return new NotDpsAoeTargetActiveTrigger(ai); }
        static Trigger* has_nearest_adds(PlayerbotAI* ai) { return new HasNearestAddsTrigger(ai); }
        static Trigger* combat_start(PlayerbotAI* ai) { return new CombatStartTrigger(ai); }
        static Trigger* combat_end(PlayerbotAI* ai) { return new CombatEndTrigger(ai); }
        static Trigger* death(PlayerbotAI* ai) { return new DeathTrigger(ai); }
        static Trigger* resurrect(PlayerbotAI* ai) { return new ResurrectTrigger(ai); }
        static Trigger* pull_start(PlayerbotAI* ai) { return new PullStartTrigger(ai); }
        static Trigger* pull_end(PlayerbotAI* ai) { return new PullEndTrigger(ai); }
        static Trigger* enemy_player_near(PlayerbotAI* ai) { return new EnemyPlayerNear(ai); }
        static Trigger* Random(PlayerbotAI* ai) { return new RandomTrigger(ai, "random", 20); }
        static Trigger* seldom(PlayerbotAI* ai) { return new RandomTrigger(ai, "seldom", 300); }
        static Trigger* often(PlayerbotAI* ai) { return new RandomTrigger(ai, "often", 5); }
        static Trigger* very_often(PlayerbotAI* ai) { return new TimeTrigger(ai, "very often", 5); }
        static Trigger* EnemyOutOfMelee(PlayerbotAI* ai) { return new EnemyOutOfMeleeTrigger(ai); }
        static Trigger* EnemyOutOfSpell(PlayerbotAI* ai) { return new EnemyOutOfSpellRangeTrigger(ai); }
        static Trigger* enemy_too_close_for_spell(PlayerbotAI* ai) { return new EnemyTooCloseForSpellTrigger(ai); }
        static Trigger* enemy_too_close_for_shoot(PlayerbotAI* ai) { return new EnemyTooCloseForShootTrigger(ai); }
        static Trigger* enemy_too_close_for_melee(PlayerbotAI* ai) { return new EnemyTooCloseForMeleeTrigger(ai); }
        static Trigger* enemy_is_close(PlayerbotAI* ai) { return new EnemyIsCloseTrigger(ai); }
        static Trigger* enemy_fifteen_yards(PlayerbotAI* ai) { return new EnemyInRangeTrigger(ai, "enemy fifteen yards", 15.0f); }
        static Trigger* enemy_ten_yards(PlayerbotAI* ai) { return new EnemyInRangeTrigger(ai, "enemy ten yards", 10.0f); }
        static Trigger* enemy_five_yards(PlayerbotAI* ai) { return new EnemyInRangeTrigger(ai, "enemy five yards", 5.0f); }
        static Trigger* party_member_to_heal_out_of_spell_range(PlayerbotAI* ai) { return new PartyMemberToHealOutOfSpellRangeTrigger(ai); }
        static Trigger* wait_for_attack_safe_distance(PlayerbotAI* ai) { return new WaitForAttackSafeDistanceTrigger(ai); }
        static Trigger* ComboPointsAvailable(PlayerbotAI* ai) { return new ComboPointsAvailableTrigger(ai); }
        static Trigger* MediumThreat(PlayerbotAI* ai) { return new MediumThreatTrigger(ai); }
        static Trigger* Dead(PlayerbotAI* ai) { return new DeadTrigger(ai); }
        static Trigger* corpse_near(PlayerbotAI* ai) { return new CorpseNearTrigger(ai); }
        static Trigger* PartyMemberDead(PlayerbotAI* ai) { return new PartyMemberDeadTrigger(ai); }
        static Trigger* PartyMemberLowHealth(PlayerbotAI* ai) { return new PartyMemberLowHealthTrigger(ai); }
        static Trigger* PartyMemberMediumHealth(PlayerbotAI* ai) { return new PartyMemberMediumHealthTrigger(ai); }
        static Trigger* PartyMemberAlmostFullHealth(PlayerbotAI* ai) { return new PartyMemberAlmostFullHealthTrigger(ai); }
        static Trigger* PartyMemberCriticalHealth(PlayerbotAI* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
        static Trigger* protect_party_member(PlayerbotAI* ai) { return new ProtectPartyMemberTrigger(ai); }
        static Trigger* no_pet(PlayerbotAI* ai) { return new NoPetTrigger(ai); }
        static Trigger* has_attackers(PlayerbotAI* ai) { return new HasAttackersTrigger(ai); }
        static Trigger* random_bot_update_trigger(PlayerbotAI* ai) { return new RandomBotUpdateTrigger(ai); }
        static Trigger* no_non_bot_players_around(PlayerbotAI* ai) { return new NoNonBotPlayersAroundTrigger(ai); }
        static Trigger* new_player_nearby(PlayerbotAI* ai) { return new NewPlayerNearbyTrigger(ai); }
        static Trigger* need_world_buff(PlayerbotAI* ai) { return new NeedWorldBuffTrigger(ai); }
        static Trigger* falling(PlayerbotAI* ai) { return new IsFallingTrigger(ai); }
        static Trigger* falling_far(PlayerbotAI* ai) { return new IsFallingFarTrigger(ai); }
        static Trigger* move_stuck(PlayerbotAI* ai) { return new MoveStuckTrigger(ai); }
        static Trigger* move_long_stuck(PlayerbotAI* ai) { return new MoveLongStuckTrigger(ai); }
        static Trigger* combat_stuck(PlayerbotAI* ai) { return new CombatStuckTrigger(ai); }
        static Trigger* combat_long_stuck(PlayerbotAI* ai) { return new CombatLongStuckTrigger(ai); }
        static Trigger* leader_is_afk(PlayerbotAI* ai) { return new LeaderIsAfkTrigger(ai); }
        static Trigger* player_wants_in_bg(PlayerbotAI* ai) { return new PlayerWantsInBattlegroundTrigger(ai); }
        static Trigger* use_trinket(PlayerbotAI* ai) { return new UseTrinketTrigger(ai); }

        static Trigger* petition_signed(PlayerbotAI* ai) { return new PetitionTurnInTrigger(ai); }
        static Trigger* buy_tabard(PlayerbotAI* ai) { return new BuyTabardTrigger(ai); }        
        static Trigger* leave_large_guild(PlayerbotAI* ai) { return new LeaveLargeGuildTrigger(ai); }

        static Trigger* val(PlayerbotAI* ai) { return new ValueTrigger(ai); }


        static Trigger* rpg(PlayerbotAI* ai) { return new RpgTrigger(ai); }
        static Trigger* rpg_wander(PlayerbotAI* ai) { return new RpgWanderTrigger(ai); }
        static Trigger* rpg_taxi(PlayerbotAI* ai) { return new RpgTaxiTrigger(ai); }
        static Trigger* rpg_discover(PlayerbotAI* ai) { return new RpgDiscoverTrigger(ai); }
        static Trigger* rpg_start_quest(PlayerbotAI* ai) { return new RpgStartQuestTrigger(ai); }
        static Trigger* rpg_end_quest(PlayerbotAI* ai) { return new RpgEndQuestTrigger(ai); }
        static Trigger* rpg_repeat_quest(PlayerbotAI* ai) { return new RpgRepeatQuestTrigger(ai); }
        static Trigger* rpg_buy(PlayerbotAI* ai) { return new RpgBuyTrigger(ai); }
        static Trigger* rpg_sell(PlayerbotAI* ai) { return new RpgSellTrigger(ai); }
        static Trigger* rpg_ah_sell(PlayerbotAI* ai) { return new RpgAHSellTrigger(ai); }
        static Trigger* rpg_ah_buy(PlayerbotAI* ai) { return new RpgAHBuyTrigger(ai); }
        static Trigger* rpg_get_mail(PlayerbotAI* ai) { return new RpgGetMailTrigger(ai); }
        static Trigger* rpg_repair(PlayerbotAI* ai) { return new RpgRepairTrigger(ai); }
        static Trigger* rpg_train(PlayerbotAI* ai) { return new RpgTrainTrigger(ai); }
        static Trigger* rpg_heal(PlayerbotAI* ai) { return new RpgHealTrigger(ai); }
        static Trigger* rpg_home_bind(PlayerbotAI* ai) { return new RpgHomeBindTrigger(ai); }
        static Trigger* rpg_queue_bg(PlayerbotAI* ai) { return new RpgQueueBGTrigger(ai); }
        static Trigger* rpg_buy_petition(PlayerbotAI* ai) { return new RpgBuyPetitionTrigger(ai); }
        static Trigger* rpg_use(PlayerbotAI* ai) { return new RpgUseTrigger(ai); }
        static Trigger* rpg_spell(PlayerbotAI* ai) { return new RpgUseTrigger(ai); }
        static Trigger* rpg_craft(PlayerbotAI* ai) { return new RpgCraftTrigger(ai); }
        static Trigger* rpg_trade_useful(PlayerbotAI* ai) { return new RpgTradeUsefulTrigger(ai); }
        static Trigger* rpg_duel(PlayerbotAI* ai) { return new RpgDuelTrigger(ai); }

        // Dungeon Triggers
        static Trigger* onyxias_lair_enter(PlayerbotAI* ai) { return new OnyxiasLairEnterDungeonTrigger(ai); }
        static Trigger* onyxias_lair_leave(PlayerbotAI* ai) { return new OnyxiasLairLeaveDungeonTrigger(ai); }
        static Trigger* molten_core_enter(PlayerbotAI* ai) { return new MoltenCoreEnterDungeonTrigger(ai); }
        static Trigger* molten_core_leave(PlayerbotAI* ai) { return new MoltenCoreLeaveDungeonTrigger(ai); }

        // Dungeon Boss Triggers
        static Trigger* onyxia_start_fight(PlayerbotAI* ai) { return new OnyxiaStartFightTrigger(ai); }
        static Trigger* onyxia_end_fight(PlayerbotAI* ai) { return new OnyxiaEndFightTrigger(ai); }
        
        static Trigger* magmadar_start_fight(PlayerbotAI* ai) { return new MagmadarStartFightTrigger(ai); }
        static Trigger* magmadar_end_fight(PlayerbotAI* ai) { return new MagmadarEndFightTrigger(ai); }
        static Trigger* magmadar_lava_bomb(PlayerbotAI* ai) { return new MagmadarLavaBombTrigger(ai); }

        static Trigger* mc_rune_in_sight(PlayerbotAI* ai) { return new MCRuneInSightTrigger(ai); }
        static Trigger* mc_rune_close(PlayerbotAI* ai) { return new MCRuneCloseTrigger(ai); }
    };
};

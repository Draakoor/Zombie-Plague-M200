/**
 * =============================================================================
 * Zombie Plague 5.0.1 Copyright (C) 2015-2016 Nikita Ushakov (Ireland, Dublin).
 * =============================================================================
 *
 * This file is part of the Zombie Plague Core.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 */

#if defined _zombieplaguemod_included
 #endinput
#endif
#define _zombieplaguemod_included

/**
 * Number of game modes.
 **/
enum
{
	MODE_INFECTION = 0,		/**< normal infection */
	MODE_MULTI,				/**< multi infection */
	MODE_SWARM,				/**< swarm mode */
	MODE_NEMESIS,			/**< nemesis round */
	MODE_SURVIVOR,			/**< survivor round */
	MODE_ARMAGEDDON			/**< armageddon round */
};

/**
 * Number of valid player classes.
 **/
enum ZPClassType
{
	TYPE_ZOMBIE	= 0,		/**< make a zombie */
	TYPE_NEMESIS,			/**< make a nemesis */
	TYPE_SURVIVOR,			/**< make a survivor */
	TYPE_HUMAN				/**< make a human */
};

/**
 * Number of valid states.
 **/
enum ZPStateType
{
	STATE_MODE_STARTED = 0,	/**< zombie round started ? */
	STATE_ROUND_NUM,		/**< number of round */
	STATE_ROUND_MODE,		/**< mode of round */
	STATE_NEW_ROUND,		/**< round not started */
	STATE_END_ROUND			/**< round ended ? */
};

/**
 * Number of valid player teams.
 **/
enum ZPClassTeam
{
	ZP_TEAM_HUMAN = 0,		/**< human team */
	ZP_TEAM_ZOMBIE,			/**< zombie team */
	ZP_TEAM_ALL				/**< all teams */
};

/**
 * Number of options.
 **/
enum ZPSelectOption
{
	NO = 0,				
	YES
}

/**
 * Number of valid player slots.
 **/
enum
{ 
	WEAPON_SLOT_INVALID = -1, 
	WEAPON_SLOT_PRIMARY, 
	WEAPON_SLOT_SECONDARY, 
	WEAPON_SLOT_MELEE, 
	WEAPON_SLOT_EQUEPMENT
};

/**
 * Called when a client became a zombie.
 * 
 * @param client			The client index.
 * @param infector			The attacker index.
 *
 * @noreturn
 **/
forward void ZP_OnClientInfected(int client, int infector);

/**
 * Called when a client became a survivor.
 * 
 * @param client			The client index.
 *
 * @noreturn
 **/
forward void ZP_OnClientHeroed(int client);

/**
 * Called after a zombie round is started.
 * 
 * @param mode				The type of round mode.
 *
 * @noreturn
 **/
forward void ZP_OnZombieModStarted(int mode);

/**
 * Called after select an extraitem in equipment menu.
 * 
 * @param client			The client index.
 * @param extraitem_index	Index of extraitem from ZP_RegisterExtraItem() native.
 *
 * @return					Plugin_Handled to block purhase. Anything else
 *                          	(like Plugin_Continue) to allow purhase and taking ammopacks.
 **/
forward Action ZP_OnExtraBuyCommand(int client, int extraitem_index);

/**
 * Called when a zombie press G button. Activation of skill.
 * 
 * @param client			The client index.
 *
 * @return					Plugin_Handled to block using skill. Anything else
 *                          	(like Plugin_Continue) to allow use.
 *
 **/
forward Action ZP_OnSkillUsed(int client);

/**
 * Called when a zombie skill duration is over, for reset variables.
 * 
 * @param client			The client index.
 *
 **/
forward void ZP_OnSkillOver(int client);

/**
 * Called when a player, deploy any weapon.
 * 
 * @param client			The client index.
 * @param weapon			The index of the weapon.
 * @param view_index		The view model index of the player.
 * @param world_index		The world model index.
 *
 * @noreturn
 **/
forward void ZP_OnWeaponDeploy(int client, int weapon, int view_index, int world_index);


/*_____________________________________________________________________________________________*/


/**
* Registers a custom class which will be added to the zombie classes menu of ZP.
*
* 	Note: The returned zombie class ID can be later used to identify
* 			the class when calling the ZP_GetClientZombieClass() natives.
*
* @param name				Caption to display on the menu.
* @param model				Player model to be used.
* @param claw_model			Knife model to be used.
* @param health				Initial health points.
* @param speed				Maximum speed.
* @param gravity			Gravity multiplier.
* @param female				Will have a female sounds.
* @param vip				Will available only for VIP players.
* @param duration			Duration of skill, for your custom addons. (0-off)
* @param countdown			Countdown of skill, for your custom addons (0-off)
*
* 	Note: The duration and countdown must be turn off together,
*	 		for disabling skill usage.
*
* @return 							An internal zombie class ID, or -1 on failure.
**/
native int ZP_RegisterZombieClass(char[] name, char[] model, char[] claw_model, int health, float speed, float gravity, ZPSelectOption female = NO, ZPSelectOption vip = NO, int duration = 0, int countdown = 0);

/**
* Registers a custom extra item which will be added to the equipment menu of ZP.
*
* 	Note: The returned extra item ID can be later used to identify
* 			the class when calling the ZP_OnExtraBuyCommand() forward.
*
* @param name				Caption to display on the menu.
* @param cost				Price of this item. (0-off any messages and ammo cost from menu)
* @param team				Which team allowed to use the item.
* @param level				The level of the player, which allow to buy item. (0-off)
* @param online				The number of players, which allowed to buy item. (0-off)
* @param limit				The number of purchases, which allowed to buy item. (0-off)
*							
*
* @return					An internal extra item ID, or -1 on failure.
**/
native int ZP_RegisterExtraItem(char[] name, int cost, ZPClassTeam team, int level = 0, int online = 0, int limit = 0);

/**
 * Returns true if the player is a VIP, false if not.
 *
 * @param client            The client index.
 *  
 * @return			        True or false.
 * @error                   Invalid client index or not connected.
 **/
native bool ZP_IsPlayerVIP(int client);

/**
 * Returns true if the player is a zombie, false if not. 
 *
 * @param client            The client index.
 *  
 * @return			        True or false.
 * @error                   Invalid client index, not connected or not alive.
 **/
native bool ZP_IsPlayerZombie(int client);

/**
 * Returns true if the player is a human, false if not.
 *
 * @param client            The client index.
 *  
 * @return			        True or false.
 * @error                   Invalid client index, not connected or not alive.
 **/
native bool ZP_IsPlayerHuman(int client);

/**
 * Returns true if the player is a nemesis, false if not. (Nemesis always have ZP_IsPlayerZombie() flag)
 *
 * @param client            The client index.
 *  
 * @return			        True or false.
 * @error                   Invalid client index, not connected or not alive.
 **/
native bool ZP_IsPlayerNemesis(int client);

/**
 * Returns true if the player is a survivor, false if not.
 *
 * @param client            The client index.
 *  
 * @return			        True or false.
 * @error                   Invalid client index, not connected or not alive.
 **/
native bool ZP_IsPlayerSurvivor(int client);

/**
 * Selects a class for the player.
 *
 * @param type              The type of class. See enum ZPClassType.
 * @param client            The client index.
 *  
 * @noreturn
 * @error                   Invalid client index or not connected.
 **/
native void ZP_SwitchClass(ZPClassType type, int client);

/**
 * Gets the amount of ammopacks of the player.
 *
 * @param client            The client index.
 *  
 * @return			        The number of ammopacks.
 * @error                   Invalid client index or not connected.
 **/
native int ZP_GetClientAmmoPack(int client);

/**
 * Gives the amount of ammopacks for the player.
 *
 * @param client            The client index.
 * @param amount            The number of ammopacks.
 *  
 * @noreturn
 * @error                   Invalid client index or not connected.
 **/
native void ZP_SetClientAmmoPack(int client, int amount);

/**
 * Gets the zombie class of the player.
 *
 * @param client            The client index.
 *  
 * @return			        The number of class.
 * @error                   Invalid client index or not connected or not alive.
 **/
native int ZP_GetClientZombieClass(int client);

/**
 * Gets the level of the player.
 *
 * @param client            The client index.
 *  
 * @return			        The number of level.
 * @error                   Invalid client index or not connected or not alive.
 **/
native int ZP_GetClientLevel(int client);

/**
 * Gets the round state.
 *
 * @param type              The mode of state. See enum ZPStateType.
 *  
 * @return			        The integer of type state.
 **/
native int ZP_GetRoundState(ZPStateType type);


/*_____________________________________________________________________________________________*/


/**
 * Sets the view weapon model.
 *
 * @param weapon     		The index of the weapon.
 * @param view_index		The view model index of the player.
 * @param model				The model index. (Must be precached)
 *
 * @noreturn
 **/
stock void ZP_SetViewModel(int weapon, int view_index, int model)
{
	// Delete model index
	SetEntProp(weapon, Prop_Send, "m_nModelIndex", 0);
	
	// Set view model for weapon
	SetEntProp(view_index, Prop_Send, "m_nModelIndex", model);
}

/**
 * Sets the world weapon model.
 *
 * @param world_index		The world model index.
 * @param model        	 	The model index. (Must be precached)
 *
 * @noreturn
 **/
stock void ZP_SetWorldModel(int world_index, int model)
{
	// Set world model for weapon
	SetEntProp(world_index, Prop_Send, "m_nModelIndex", model);
}

/**
 * Returns true if the player is connected and alive, false if not.
 *
 * @param client			The client index.
 * @param aliveness			Set to true to validate that the client is alive, false to ignore.
 *  
 * @return					True or false.
 **/
stock bool IsPlayerExist(int client, bool aliveness = true)
{
	// If client is't valid
	if (client <= 0 || client > MaxClients)
	{
		return false;
	}
	
	// If client isn't connected
	if (!IsClientConnected(client))
	{
		return false;
	}

	// If client isn't in game
	if (!IsClientInGame(client))
	{
		return false;
	}

	// If client isn't alive
	if(aliveness && !IsPlayerAlive(client))
	{
		return false;
	}
	
	// If client exist
	return true;
}

/**
 * Returns true if the player has a current weapon, false if not.
 *
 * @param client			The client index.
 * @param weapon			The weapon's classname.
 *
 * @return					True or false.
 **/
stock bool IsPlayerHasWeapon(int client, char weapon[32])
{
	// Initialize char
	char classname[32];

	// Get number of the entities
	int size = GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons");

	// i = number of the entity
	for (int i = 0; i < size; i++)
	{
		// Get index of the entity
		int index = GetEntPropEnt(client, Prop_Send, "m_hMyWeapons", i);
		
		// Verify that the entity is valid
		if (IsValidEdict(index))
		{
			// Get classname of the entity
			GetEdictClassname(index, classname, sizeof(classname));
			
			// If entity find
			if (StrEqual(classname, weapon, false))
			{
				return true;
			}
		}
		
		// Go to next weapon
		continue;
	}

	// If didn't find
	return false;
}  
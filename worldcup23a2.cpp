#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    this->teamIdTree = new TeamTree<TeamId>();
    this->teamStatsTree = new TeamTree<TeamStats>();
    this->hashTable = new PlayerTable();
    this->removedTeamsPlayersTeam = new Team();
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
	if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team = this->teamIdTree->search(id);

    delete id;

    if (team != nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        team = new Team(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    try
    {
        this->teamIdTree->insert(team);
        this->teamStatsTree->insert(team);
    }
    catch (const std::bad_alloc& e)
    {
        delete team;
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team = this->teamIdTree->search(id);

    delete id;

    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }

    this->teamIdTree->remove(team);
    this->teamStatsTree->remove(team);

    if (team->getNumPlayers() == 0)
    {
        delete team;
    }
    else
    {
        team->getPlayersTreeRoot()->unionInto(this->removedTeamsPlayersTeam);
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t& spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    PlayerNode* node = this->hashTable->member(playerId);
    if (node != nullptr)
    {
        return StatusType::FAILURE;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team = this->teamIdTree->search(id);

    delete id;

    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }

    Player* player;
    try
    {
        player = new Player(playerId, cards);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    try
    {
        node = team->addPlayer(player, gamesPlayed, spirit, ability, goalKeeper);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    try
    {
        this->hashTable->insert(node);
        this->teamIdTree->remove(team);
        this->teamStatsTree->remove(team);
        this->teamIdTree->insert(team);
        this->teamStatsTree->insert(team);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId1);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team1 = this->teamIdTree->search(id);

    delete id;

    if (team1 == nullptr || !team1->isValid())
    {
        return StatusType::FAILURE;
    }

    try
    {
        id = new TeamId(teamId2);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team2 = this->teamIdTree->search(id);

    delete id;

    if (team2 == nullptr || !team2->isValid())
    {
        return StatusType::FAILURE;
    }

    team1->increaseGamesPlayed(1);
    team2->increaseGamesPlayed(1);

    if (team1->getPower() < team2->getPower())
    {
        team1->addPoints(LOSE_POINTS);
        team2->addPoints(WIN_POINTS);
        return 3;
    }
    if (team1->getPower() > team2->getPower())
    {
        team1->addPoints(WIN_POINTS);
        team2->addPoints(LOSE_POINTS);
        return 1;
    }
    if (team1->getSpiritStrength() < team2->getSpiritStrength())
    {
        team1->addPoints(LOSE_POINTS);
        team2->addPoints(WIN_POINTS);
        return 4;
    }
    if (team1->getSpiritStrength() > team2->getSpiritStrength())
    {
        team1->addPoints(WIN_POINTS);
        team2->addPoints(LOSE_POINTS);
        return 2;
    }
    team1->addPoints(TIE_POINTS);
    team2->addPoints(TIE_POINTS);
    return 0;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    PlayerNode* node = this->hashTable->member(playerId);
    if (node == nullptr)
    {
        return StatusType::FAILURE;
    }

    int gamesPlayed = node->getGamesPlayed();

    return gamesPlayed;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if (playerId <= 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    PlayerNode* node = this->hashTable->member(playerId);
    if (node == nullptr)
    {
        return StatusType::FAILURE;
    }

    if (node->findTeam() == this->removedTeamsPlayersTeam)
    {
        return StatusType::FAILURE;
    }

    node->getPlayer()->addCards(cards);

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    PlayerNode* node = this->hashTable->member(playerId);
    if (node == nullptr)
    {
        return StatusType::FAILURE;
    }

	return node->getPlayer()->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team = this->teamIdTree->search(id);

    delete id;

    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }

    return team->getPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	Team* team = this->teamStatsTree->getIthTeam(i);

    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }

	return team->getId();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    PlayerNode* node = this->hashTable->member(playerId);
    if (node == nullptr)
    {
        return StatusType::FAILURE;
    }

    permutation_t partialSpirit = node->getPartialSpirit();

    return partialSpirit;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamId* id;
    try
    {
        id = new TeamId(teamId1);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team1 = this->teamIdTree->search(id);

    delete id;

    if (team1 == nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        id = new TeamId(teamId2);
    }
    catch (const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    Team* team2 = this->teamIdTree->search(id);

    delete id;

    if (team2 == nullptr)
    {
        return StatusType::FAILURE;
    }

    this->teamIdTree->remove(team2);
    this->teamStatsTree->remove(team2);

    team1->buy(team2);

	return StatusType::SUCCESS;
}

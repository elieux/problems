#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

typedef unsigned int uint;

typedef struct {
	uint i;
	uint n;
} Team;

typedef struct {
	uint i;
	uint n;
} Table;

typedef std::vector<Team> Teams;
typedef std::vector<Table> Tables;
typedef std::vector<uint> Placement;
typedef std::vector<Placement> Placements;

bool operator<(const Team &a, const Team &b) {
	return a.n < b.n;
}

bool operator>(const Team &a, const Team &b) {
	return a.n > b.n;
}

bool operator<=(const Team &a, const Team &b) {
	return a.n <= b.n;
}

bool operator==(const Team &a, const Team &b) {
	return a.n == b.n;
}

bool operator>=(const Team &a, const Team &b) {
	return a.n >= b.n;
}

bool operator<(const Table &a, const Table &b) {
	return a.n < b.n;
}

bool operator>(const Table &a, const Table &b) {
	return a.n > b.n;
}

bool operator<=(const Table &a, const Table &b) {
	return a.n <= b.n;
}

bool operator==(const Table &a, const Table &b) {
	return a.n == b.n;
}

bool operator>=(const Table &a, const Table &b) {
	return a.n >= b.n;
}

void solve(uint nTeams, uint nTables) {
	Teams teams(nTeams);
	Tables tables(nTables);
	
	Placements placements;
	uint sumTablesN = 0, sumTeamsN = 0;
	
	for (uint iTeam = 0; iTeam < nTeams; iTeam++)
	{
		Team &team = teams[iTeam];
		
		team.i = iTeam;
		scanf("%u", &team.n);
		
		sumTeamsN += team.n;
		placements.push_back(Placement(team.n));
	}
	for (uint iTable = 0; iTable < nTables; iTable++)
	{
		Table &table = tables[iTable];
		
		table.i = iTable;
		scanf("%u", &table.n);
		
		sumTablesN += table.n;
	}
	
	if (sumTablesN < sumTeamsN)
	{
		printf("0\n");
		return;
	}
	
	std::sort(teams.begin(), teams.end(), std::greater<Team>());
	std::sort(tables.begin(), tables.end(), std::greater<Table>());
	
	Tables::iterator beginTable = tables.begin(), iTable = beginTable, endTable = tables.end();
	uint nFullTables = 0;
	for (Teams::iterator iTeam = teams.begin(), endTeam = teams.end(); iTeam != endTeam; iTeam++)
	{
		Team &team = *iTeam;
		
		while (team.n > 0)
		{
			if (nFullTables == nTables)
			{
				printf("0\n");
				return;
			}
			
			if ((*iTable).n > 0)
			{
				team.n--;
				placements[team.i][team.n] = (*iTable).i;
				
				(*iTable).n--;
				if ((*iTable).n == 0)
					nFullTables++;
			}
			
			iTable++;
			if (iTable == endTable)
				iTable = beginTable;
		}
	}
	
	for (Placements::iterator iPlacement = placements.begin(), endPlacement = placements.end(); iPlacement != endPlacement; iPlacement++)
	{
		Placement &placement = *iPlacement;
		std::sort(placement.begin(), placement.end());
		for (Placement::iterator beginPlace = placement.begin(), iPlace = beginPlace, endPlace = placement.end(); iPlace != endPlace; iPlace++)
			if (iPlace != beginPlace && *iPlace == *(iPlace - 1))
			{
				printf("0\n");
				return;
			}
	}
	
	printf("1\n");
	for (Placements::iterator iPlacement = placements.begin(), endPlacement = placements.end(); iPlacement != endPlacement; iPlacement++)
	{
		const Placement &placement = *iPlacement;
		for (Placement::const_iterator beginPlace = placement.begin(), iPlace = beginPlace, endPlace = placement.end(); iPlace != endPlace; iPlace++)
			printf("%s%u", iPlace == beginPlace ? "" : " ", *iPlace + 1);
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	
	while (true)
	{
		uint nTeams, nTables;
		
		scanf("%u %u", &nTeams, &nTables);
		if (nTeams == 0 && nTables == 0)
			break;
		
		solve(nTeams, nTables);
	}
	
	return 0;
}

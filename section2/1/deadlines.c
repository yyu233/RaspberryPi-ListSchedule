// Generated deadlines for the test workload
// This file has to be included only in main_week4.c
long long workloadDeadlines[] = {
	160000,
	400000,
	400000,
	240000,
	240000,
	480000,
	320000,
	120000,
};

int workloadDependencies[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
};
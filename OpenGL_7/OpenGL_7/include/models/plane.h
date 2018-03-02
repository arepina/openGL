const uint32_t vcount = 110;
const uint32_t icount = 486;

const vertex vertices[vcount] = {
	{{-0.777778f * size, -0.000000f * size, 0.777778f * size}, {0.222222f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, -0.000000f * size, 0.777778f * size}, {0.111111f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, -0.000001f * size, 1.000000f * size}, {0.111111f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, -0.000001f * size, 1.000000f * size}, {0.222222f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, -0.000000f * size, 0.777778f * size}, {0.333333f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, -0.000001f * size, 1.000000f * size}, {0.333333f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, -0.000000f * size, 0.777778f * size}, {0.444444f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, -0.000001f * size, 1.000000f * size}, {0.444444f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, -0.000000f * size, 0.777778f * size}, {0.555556f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, -0.000001f * size, 1.000000f * size}, {0.555556f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, -0.000000f * size, 0.777778f * size}, {0.666667f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, -0.000001f * size, 1.000000f * size}, {0.666667f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, -0.000000f * size, 0.777778f * size}, {0.777778f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, -0.000001f * size, 1.000000f * size}, {0.777778f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, -0.000000f * size, 0.777778f * size}, {0.888889f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, -0.000001f * size, 1.000000f * size}, {0.888889f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.777778f * size}, {1.000000f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000001f * size, 1.000000f * size}, {1.000000f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, -0.000000f * size, 0.777778f * size}, {0.111111f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.777778f * size}, {0.000000f, 0.888889f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000001f * size, 1.000000f * size}, {0.000000f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, -0.000001f * size, 1.000000f * size}, {0.111111f, 1.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, -0.000000f * size, 0.555556f * size}, {0.111111f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.555556f * size}, {0.000000f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.555556f * size}, {1.000000f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, -0.000000f * size, 0.555556f * size}, {0.888889f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, -0.000000f * size, 0.555556f * size}, {0.777778f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, -0.000000f * size, 0.555556f * size}, {0.666667f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, -0.000000f * size, 0.555556f * size}, {0.555556f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, -0.000000f * size, 0.555556f * size}, {0.444444f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, -0.000000f * size, 0.555556f * size}, {0.333333f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, -0.000000f * size, 0.555556f * size}, {0.222222f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, -0.000000f * size, 0.555556f * size}, {0.111111f, 0.777778f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, -0.000000f * size, 0.333333f * size}, {0.222222f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, -0.000000f * size, 0.333333f * size}, {0.111111f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, -0.000000f * size, 0.333333f * size}, {0.333333f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, -0.000000f * size, 0.333333f * size}, {0.444444f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, -0.000000f * size, 0.333333f * size}, {0.555556f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, -0.000000f * size, 0.333333f * size}, {0.666667f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, -0.000000f * size, 0.333333f * size}, {0.777778f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, -0.000000f * size, 0.333333f * size}, {0.888889f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.333333f * size}, {1.000000f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, -0.000000f * size, 0.333333f * size}, {0.111111f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.333333f * size}, {0.000000f, 0.666667f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, -0.000000f * size, 0.111111f * size}, {0.111111f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.111111f * size}, {0.000000f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, -0.000000f * size, 0.111111f * size}, {1.000000f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, -0.000000f * size, 0.111111f * size}, {0.888889f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, -0.000000f * size, 0.111111f * size}, {0.777778f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, -0.000000f * size, 0.111111f * size}, {0.666667f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, -0.000000f * size, 0.111111f * size}, {0.555556f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, -0.000000f * size, 0.111111f * size}, {0.444444f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, -0.000000f * size, 0.111111f * size}, {0.333333f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, -0.000000f * size, 0.111111f * size}, {0.222222f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, -0.000000f * size, 0.111111f * size}, {0.111111f, 0.555556f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, 0.000000f * size, -0.111111f * size}, {0.222222f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, 0.000000f * size, -0.111111f * size}, {0.111111f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, 0.000000f * size, -0.111111f * size}, {0.333333f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, 0.000000f * size, -0.111111f * size}, {0.444444f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, 0.000000f * size, -0.111111f * size}, {0.555556f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, 0.000000f * size, -0.111111f * size}, {0.666667f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, 0.000000f * size, -0.111111f * size}, {0.777778f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, 0.000000f * size, -0.111111f * size}, {0.888889f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.111111f * size}, {1.000000f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, 0.000000f * size, -0.111111f * size}, {0.111111f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.111111f * size}, {0.000000f, 0.444444f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, 0.000000f * size, -0.333333f * size}, {0.111111f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.333333f * size}, {0.000000f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.333333f * size}, {1.000000f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, 0.000000f * size, -0.333333f * size}, {0.888889f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, 0.000000f * size, -0.333333f * size}, {0.777778f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, 0.000000f * size, -0.333333f * size}, {0.666667f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, 0.000000f * size, -0.333333f * size}, {0.555556f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, 0.000000f * size, -0.333333f * size}, {0.444444f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, 0.000000f * size, -0.333333f * size}, {0.333333f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, 0.000000f * size, -0.333333f * size}, {0.222222f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, 0.000000f * size, -0.333333f * size}, {0.111111f, 0.333333f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, 0.000000f * size, -0.555556f * size}, {0.222222f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, 0.000000f * size, -0.555556f * size}, {0.111111f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, 0.000000f * size, -0.555556f * size}, {0.333333f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, 0.000000f * size, -0.555556f * size}, {0.444444f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, 0.000000f * size, -0.555556f * size}, {0.555556f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, 0.000000f * size, -0.555556f * size}, {0.666667f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, 0.000000f * size, -0.555556f * size}, {0.777778f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, 0.000000f * size, -0.555556f * size}, {0.888889f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.555556f * size}, {1.000000f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, 0.000000f * size, -0.555556f * size}, {0.111111f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.555556f * size}, {0.000000f, 0.222222f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, 0.000000f * size, -0.777778f * size}, {0.111111f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.777778f * size}, {0.000000f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000000f * size, -0.777778f * size}, {1.000000f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, 0.000000f * size, -0.777778f * size}, {0.888889f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, 0.000000f * size, -0.777778f * size}, {0.777778f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, 0.000000f * size, -0.777778f * size}, {0.666667f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, 0.000000f * size, -0.777778f * size}, {0.555556f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, 0.000000f * size, -0.777778f * size}, {0.444444f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, 0.000000f * size, -0.777778f * size}, {0.333333f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, 0.000000f * size, -0.777778f * size}, {0.222222f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, 0.000000f * size, -0.777778f * size}, {0.111111f, 0.111111f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.777778f * size, 0.000001f * size, -1.000000f * size}, {0.222222f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-1.000000f * size, 0.000001f * size, -1.000000f * size}, {0.111111f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.555556f * size, 0.000001f * size, -1.000000f * size}, {0.333333f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.333333f * size, 0.000001f * size, -1.000000f * size}, {0.444444f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{-0.111111f * size, 0.000001f * size, -1.000000f * size}, {0.555556f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.111111f * size, 0.000001f * size, -1.000000f * size}, {0.666667f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.333333f * size, 0.000001f * size, -1.000000f * size}, {0.777778f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.555556f * size, 0.000001f * size, -1.000000f * size}, {0.888889f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000001f * size, -1.000000f * size}, {1.000000f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{1.000000f * size, 0.000001f * size, -1.000000f * size}, {0.111111f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
	{{0.777778f * size, 0.000001f * size, -1.000000f * size}, {0.000000f, 0.000000f}, {0.000000f, 1.000000f, 0.000000f}},
};

const uint32_t indices[icount] = {
	0, 1, 2,
	0, 2, 3,
	4, 0, 3,
	4, 3, 5,
	6, 4, 5,
	6, 5, 7,
	8, 6, 7,
	8, 7, 9,
	10, 8, 9,
	10, 9, 11,
	12, 10, 11,
	12, 11, 13,
	14, 12, 13,
	14, 13, 15,
	16, 14, 15,
	16, 15, 17,
	18, 19, 20,
	18, 20, 21,
	22, 23, 19,
	22, 19, 18,
	24, 25, 14,
	24, 14, 16,
	25, 26, 12,
	25, 12, 14,
	26, 27, 10,
	26, 10, 12,
	27, 28, 8,
	27, 8, 10,
	28, 29, 6,
	28, 6, 8,
	29, 30, 4,
	29, 4, 6,
	30, 31, 0,
	30, 0, 4,
	31, 32, 1,
	31, 1, 0,
	33, 34, 32,
	33, 32, 31,
	35, 33, 31,
	35, 31, 30,
	36, 35, 30,
	36, 30, 29,
	37, 36, 29,
	37, 29, 28,
	38, 37, 28,
	38, 28, 27,
	39, 38, 27,
	39, 27, 26,
	40, 39, 26,
	40, 26, 25,
	41, 40, 25,
	41, 25, 24,
	42, 43, 23,
	42, 23, 22,
	44, 45, 43,
	44, 43, 42,
	46, 47, 40,
	46, 40, 41,
	47, 48, 39,
	47, 39, 40,
	48, 49, 38,
	48, 38, 39,
	49, 50, 37,
	49, 37, 38,
	50, 51, 36,
	50, 36, 37,
	51, 52, 35,
	51, 35, 36,
	52, 53, 33,
	52, 33, 35,
	53, 54, 34,
	53, 34, 33,
	55, 56, 54,
	55, 54, 53,
	57, 55, 53,
	57, 53, 52,
	58, 57, 52,
	58, 52, 51,
	59, 58, 51,
	59, 51, 50,
	60, 59, 50,
	60, 50, 49,
	61, 60, 49,
	61, 49, 48,
	62, 61, 48,
	62, 48, 47,
	63, 62, 47,
	63, 47, 46,
	64, 65, 45,
	64, 45, 44,
	66, 67, 65,
	66, 65, 64,
	68, 69, 62,
	68, 62, 63,
	69, 70, 61,
	69, 61, 62,
	70, 71, 60,
	70, 60, 61,
	71, 72, 59,
	71, 59, 60,
	72, 73, 58,
	72, 58, 59,
	73, 74, 57,
	73, 57, 58,
	74, 75, 55,
	74, 55, 57,
	75, 76, 56,
	75, 56, 55,
	77, 78, 76,
	77, 76, 75,
	79, 77, 75,
	79, 75, 74,
	80, 79, 74,
	80, 74, 73,
	81, 80, 73,
	81, 73, 72,
	82, 81, 72,
	82, 72, 71,
	83, 82, 71,
	83, 71, 70,
	84, 83, 70,
	84, 70, 69,
	85, 84, 69,
	85, 69, 68,
	86, 87, 67,
	86, 67, 66,
	88, 89, 87,
	88, 87, 86,
	90, 91, 84,
	90, 84, 85,
	91, 92, 83,
	91, 83, 84,
	92, 93, 82,
	92, 82, 83,
	93, 94, 81,
	93, 81, 82,
	94, 95, 80,
	94, 80, 81,
	95, 96, 79,
	95, 79, 80,
	96, 97, 77,
	96, 77, 79,
	97, 98, 78,
	97, 78, 77,
	99, 100, 98,
	99, 98, 97,
	101, 99, 97,
	101, 97, 96,
	102, 101, 96,
	102, 96, 95,
	103, 102, 95,
	103, 95, 94,
	104, 103, 94,
	104, 94, 93,
	105, 104, 93,
	105, 93, 92,
	106, 105, 92,
	106, 92, 91,
	107, 106, 91,
	107, 91, 90,
	108, 109, 89,
	108, 89, 88,
};

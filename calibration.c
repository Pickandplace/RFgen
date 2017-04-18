/*
 * uint16_t calibration.c
 *
 * Created: 12/3/2016 5:07:21 PM
 *  Author: Jean
 */ 
#include <asf.h>
#include <LMX2592.h>
extern LMX2592_t LMX2592;

uint16_t cal_0_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 12086, 12085, 12084, 10546, 10545, 10544, 11055, 11054, 11053, 11052, 11051, 11050, 11049, 11048, 11047, 11046, 11045, 11044, 11043, 11042, 11041, 11040, 11039, 11038, 11037, 11036, 11035, 11034, 11033, 11032, 11031, 11030, 11029, 11028, 11027, 11026, 11025, 11024, 11023, 11022, 11021, 11020, 11019, 11018, 11017, 11016, 11015, 11014, 11013, 11012, 11011, 11010, 11009, 11008, 11008};
uint16_t cal_0_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 12086, 12085, 12084, 10546, 10545, 10544, 11055, 11054, 11053, 11052, 11051, 11050, 11049, 11048, 11047, 11046, 11045, 11044, 11043, 11042, 11041, 11040, 11039, 11038, 11037, 11036, 11035, 11034, 11033, 11032, 11031, 11030, 11029, 11028, 11027, 11026, 11025, 11024, 11023, 11022, 11021, 11020, 11019, 11018, 11017, 11016, 11015, 11014, 11013, 11012, 11011, 11010, 11009, 11008, 11008};
uint16_t cal_1_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 12089, 12088, 12087, 12086, 12085, 12084, 12083, 12082, 12081, 12080, 12079, 12078, 12077, 12076, 12075, 12074, 12073, 12072, 12071, 12070, 12069, 12068, 12067, 12066, 12065, 12064, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_1_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 12089, 12088, 12087, 12086, 12085, 12084, 12083, 12082, 12081, 12080, 12079, 12078, 12077, 12076, 12075, 12074, 12073, 12072, 12071, 12070, 12069, 12068, 12067, 12066, 12065, 12064, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_2_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 9023, 10303, 12095, 12094, 12093, 12092, 12091, 12090, 10552, 10551, 10550, 10549, 10548, 10547, 10546, 10545, 10544, 10543, 10542, 10541, 10540, 10539, 10538, 10537, 10536, 10535, 10534, 10533, 10532, 10531, 10530, 10529, 10528, 10527, 10526, 10525, 10524, 10523, 10522, 10521, 10520, 10519, 10518, 10517, 10516, 10515, 10514, 10513, 10512, 10511, 10510, 10509, 10508, 10507, 10506, 10505, 10504, 10503, 10502, 10501, 10500, 10499, 10498, 10497, 10496, 10496};
uint16_t cal_2_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 12085, 12084, 12083, 10545, 10544, 10543, 11054, 11053, 11052, 11051, 11050, 11049, 11048, 11047, 11046, 11045, 11044, 11043, 11042, 11041, 11040, 11039, 11038, 11037, 11036, 11035, 11034, 11033, 11032, 11031, 11030, 11029, 11028, 11027, 11026, 11025, 11024, 11023, 11022, 11021, 11020, 11019, 11018, 11017, 11016, 11015, 11014, 11013, 11012, 11011, 11010, 11009, 11008, 11008};
uint16_t cal_3_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 11807, 11806, 11805, 11804, 11803, 11802, 11801, 11800, 11799, 11798, 11797, 11796, 11795, 11794, 11793, 11792, 11791, 11790, 11789, 11788, 11787, 11786, 11785, 11784, 11783, 11782, 11781, 11780, 11779, 11778, 11777, 11776};
uint16_t cal_3_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2109, 2108, 2107, 2106, 2105, 4159, 4158, 4157, 4156, 4155, 6463, 6462, 6461, 9023, 10303, 12095, 12094, 12093, 12092, 12091, 12090, 12089, 12088, 12087, 12086, 12085, 12084, 12083, 10545, 10544, 10543, 11054, 11053, 11052, 11307, 11306, 11305, 11304, 11303, 11302, 11301, 11300, 11299, 11298, 11297, 11296, 11295, 11294, 11293, 11292, 11291, 11290, 11289, 11288, 11287, 11286, 11285, 11284, 11283, 11282, 11281, 11280, 11279, 11278, 11277, 11276, 11275, 11274, 11273, 11272, 11271, 11270, 11269, 11268, 11267, 11266, 11265, 11264, 11264};
uint16_t cal_4_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 12081, 12080, 12079, 10541, 10540, 10539, 11050, 11049, 11048, 11047, 11046, 11045, 11044, 11043, 11042, 11041, 11040, 11039, 11038, 11037, 11036, 11035, 11034, 11033, 11032, 11031, 11030, 11029, 11028, 11027, 11026, 11025, 11024, 11023, 11022, 11021, 11020, 11019, 11018, 11017, 11016, 11015, 11014, 11013, 11012, 11011, 11010, 11009, 11008, 11008};
uint16_t cal_4_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 12092, 12091, 12090, 12089, 12088, 12087, 12086, 12085, 10547, 10546, 10545, 10544, 10543, 10542, 10541, 10540, 10539, 10538, 10537, 10536, 10535, 10534, 10533, 10532, 10531, 10530, 10529, 10528, 10527, 10526, 10525, 10524, 10523, 10522, 10521, 10520, 10519, 10518, 10517, 10516, 10515, 10514, 10513, 10512, 10511, 10510, 10509, 10508, 10507, 10506, 10505, 10504, 10503, 10502, 10501, 10500, 10499, 10498, 10497, 10496, 10496};
uint16_t cal_5_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 12080, 12079, 12078, 12077, 12076, 12075, 12074, 12073, 12072, 12071, 12070, 12069, 12068, 12067, 12066, 12065, 12064, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_5_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4157, 4156, 4155, 6463, 6462, 6461, 9023, 10303, 12095, 12094, 12093, 12092, 12091, 12090, 12089, 12088, 12087, 12086, 12085, 12084, 12083, 12082, 12081, 12080, 12079, 12078, 12077, 12076, 10538, 10537, 10536, 11047, 11046, 11045, 11300, 11299, 11298, 11297, 11296, 11295, 11294, 11293, 11292, 11291, 11290, 11289, 11288, 11287, 11286, 11285, 11284, 11283, 11282, 11281, 11280, 11279, 11278, 11277, 11276, 11275, 11274, 11273, 11272, 11271, 11270, 11269, 11268, 11267, 11266, 11265, 11264, 11264};
uint16_t cal_6_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 12073, 12072, 12071, 10533, 10532, 10531, 11042, 11041, 11040, 11039, 11038, 11037, 11036, 11035, 11034, 11033, 11032, 11031, 11030, 11029, 11028, 11027, 11026, 11025, 11024, 11023, 11022, 11021, 11020, 11019, 11018, 11017, 11016, 11015, 11014, 11013, 11012, 11011, 11010, 11009, 11008, 11008};
uint16_t cal_6_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 11807, 11806, 11805, 11804, 11803, 11802, 11801, 11800, 11799, 11798, 11797, 11796, 11795, 11794, 11793, 11792, 11791, 11790, 11789, 11788, 11787, 11786, 11785, 11784, 11783, 11782, 11781, 11780, 11779, 11778, 11777, 11776};
uint16_t cal_7_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 12071, 12070, 12069, 12068, 12067, 12066, 12065, 12064, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_7_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 12093, 12092, 12091, 12090, 12089, 12088, 12087, 12086, 12085, 12084, 12083, 12082, 12081, 12080, 12079, 12078, 12077, 12076, 12075, 12074, 12073, 12072, 12071, 12070, 12069, 12068, 12067, 12066, 10528, 10527, 10526, 11037, 11036, 11035, 11290, 11289, 11288, 11287, 11286, 11285, 11284, 11283, 11282, 11281, 11280, 11279, 11278, 11277, 11276, 11275, 11274, 11273, 11272, 11271, 11270, 11269, 11268, 11267, 11266, 11265, 11264, 11264};
uint16_t cal_8_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 12067, 12066, 12065, 12064, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_8_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 11807, 11806, 11805, 11804, 11803, 11802, 11801, 11800, 11799, 11798, 11797, 11796, 11795, 11794, 11793, 11792, 11791, 11790, 11789, 11788, 11787, 11786, 11785, 11784, 11783, 11782, 11781, 11780, 11779, 11778, 11777, 11776};
uint16_t cal_9_0[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 12063, 12062, 12061, 12060, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};
uint16_t cal_9_5[]=  {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 11807, 11806, 11805, 11804, 11803, 11802, 11801, 11800, 11799, 11798, 11797, 11796, 11795, 11794, 11793, 11792, 11791, 11790, 11789, 11788, 11787, 11786, 11785, 11784, 11783, 11782, 11781, 11780, 11779, 11778, 11777, 11776};
uint16_t cal_10_0[]= {575, 831, 830, 1087, 1343, 1599, 1855, 1854, 2367, 2366, 2879, 2878, 3391, 3390, 3389, 4415, 4927, 5439, 5951, 5950, 5949, 7743, 8767, 9791, 11839, 11838, 11837, 11836, 11835, 11834, 11833, 11832, 11831, 11830, 11829, 11828, 11827, 11826, 11825, 11824, 11823, 11822, 11821, 11820, 11819, 11818, 11817, 11816, 11815, 11814, 11813, 11812, 11811, 11810, 11809, 11808, 11807, 11806, 11805, 11804, 12059, 12058, 12057, 12056, 12055, 12054, 12053, 12052, 12051, 12050, 12049, 12048, 12047, 12046, 12045, 12044, 12043, 12042, 12041, 12040, 12039, 12038, 12037, 12036, 12035, 12034, 12033, 12032};

int16_t max_pow_out[] = {250, 250, 250, 250, 245, 245, 245, 230, 225, 220, 205, 195, 185, 170, 160, 145, 140, 135, 120, 110, 100};
int16_t min_pow_out[] = {-183, -183, -186, -186, -187, -188, -190, -204, -208, -212, -231, -239, -248, -265, -276, -289, -296, -300, -316, -325, -336};

#include <stdio.h>
int main(){
int tab_lena[64][64] = {{0,1,2,0,3,4,5,0,6,7,8,0,9,10,11,0,12,13,14,0,15,16,17,0,18,19,20,0,21,22,23,0,24,25,26,0,27,28,29,0,30,31,32,0,33,34,35,0,36,37,38,0,39,40,41,0,42,43,44,0,45,46,47,0},{48,49,50,0,51,52,53,0,54,55,56,0,57,58,59,0,60,61,62,0,63,64,65,0,66,67,68,0,69,70,71,0,72,73,74,0,75,76,77,0,78,79,80,0,81,82,83,0,84,85,86,0,87,88,89,0,90,91,92,0,93,94,95,0},{96,97,98,0,99,100,101,0,102,103,104,0,105,106,107,0,108,109,110,0,111,112,113,0,114,115,116,0,117,118,119,0,120,121,122,0,123,124,125,0,126,127,128,0,129,130,131,0,132,133,134,0,135,136,137,0,138,139,140,0,141,142,143,0},{144,145,146,0,147,148,149,0,150,151,152,0,153,154,155,0,156,157,158,0,159,160,161,0,162,163,164,0,165,166,167,0,168,169,170,0,171,172,173,0,174,175,176,0,177,178,179,0,180,181,182,0,183,184,185,0,186,187,188,0,189,190,191,0},{192,193,194,0,195,196,197,0,198,199,200,0,201,202,203,0,204,205,206,0,207,208,209,0,210,211,212,0,213,214,215,0,216,217,218,0,219,220,221,0,222,223,224,0,225,226,227,0,228,229,230,0,231,232,233,0,234,235,236,0,237,238,239,0},{240,241,242,0,243,244,245,0,246,247,248,0,249,250,251,0,252,253,254,0,255,30,31,72,190,186,83,131,157,161,157,70,22,34,40,50,37,37,59,28,32,18,43,49,69,19,57,24,45,55,47,58,68,76,87,89,97,93,93,98,96,95,102,99},{102,109,112,109,109,113,118,119,120,123,133,129,140,144,152,170,179,186,195,196,199,73,66,79,97,103,92,95,107,82,60,49,62,65,60,99,105,67,33,19,44,71,20,26,37,188,190,135,109,154,160,163,73,36,15,20,41,45,53,47,72,33,98,51},{71,111,14,61,26,76,103,23,50,62,76,80,88,91,93,93,92,95,99,100,93,100,104,109,112,114,114,113,116,121,119,121,128,136,142,152,162,176,184,192,200,206,61,72,74,89,100,92,88,103,92,61,57,52,62,58,74,110,93,46,23,26,50,65},{28,31,165,194,177,91,143,159,163,148,44,22,31,34,34,53,37,67,24,69,62,99,47,25,47,42,64,103,12,30,53,68,80,85,88,93,93,97,98,94,105,97,105,109,104,112,113,113,112,118,118,116,122,127,131,139,149,163,173,183,192,198,201,58},{63,77,91,91,97,85,87,95,74,63,59,56,57,59,97,103,69,31,27,36,61,27,36,98,193,189,80,127,156,158,159,99,21,24,34,28,41,23,21,49,26,29,128,18,43,23,79,44,85,11,16,47,68,76,83,81,97,91,94,96,93,100,102,102},{104,102,112,115,117,115,119,120,116,120,124,131,143,145,158,172,182,191,199,202,147,61,78,86,96,92,86,79,87,88,64,77,64,54,45,71,104,84,59,25,30,41,25,25,47,188,194,110,106,154,161,163,109,30,39,21,30,33,25,13,117,26,97,125},{16,84,13,88,47,73,21,13,26,54,70,78,83,88,86,88,96,93,96,103,100,101,105,104,107,115,112,112,114,117,121,123,125,136,150,159,168,180,190,196,201,202,55,71,84,97,95,86,81,76,87,75,61,71,54,46,48,87,98,75,42,34,25,50},{30,41,141,193,150,90,144,160,166,139,27,30,26,28,29,39,51,27,23,66,82,34,85,16,67,21,97,36,24,20,32,63,77,78,87,90,95,92,94,96,99,103,104,108,107,111,114,113,116,114,111,114,119,122,132,143,156,166,175,189,196,200,206,46},{67,81,90,96,84,85,74,70,81,58,67,65,43,40,59,96,89,63,36,33,27,37,44,93,178,163,73,129,160,162,161,60,45,24,21,38,36,71,18,52,18,38,30,73,26,66,26,97,42,17,19,17,42,65,78,84,89,92,93,93,103,103,101,105},{103,106,108,115,115,112,112,114,116,119,122,129,138,150,160,174,183,194,201,203,52,66,81,88,93,97,87,72,68,78,66,51,70,54,48,45,78,96,84,43,30,26,31,39,64,158,163,88,106,152,160,164,137,49,25,31,32,36,58,21,66,18,79,66},{37,45,50,36,88,83,17,20,14,28,55,71,79,86,89,92,91,95,100,101,102,105,109,107,112,110,111,111,108,113,115,118,131,137,146,163,175,184,193,202,204,148,63,74,85,86,94,84,77,70,63,73,53,55,73,54,41,58,91,88,67,37,33,26},{32,65,138,167,108,88,147,159,162,142,32,27,40,27,32,29,23,42,33,63,90,19,91,44,42,104,75,28,31,17,14,33,52,57,83,84,90,94,94,101,102,101,107,107,109,115,110,110,115,112,108,110,122,127,132,144,162,174,181,190,203,203,204,56},{74,85,88,83,89,82,84,58,57,57,41,72,68,46,35,81,95,84,47,34,26,32,69,110,169,138,69,128,155,162,158,91,21,18,25,39,28,23,28,77,36,87,33,84,23,55,63,113,31,17,20,16,12,22,46,61,84,90,95,91,100,106,106,102},{104,107,110,114,110,110,106,110,111,116,126,134,145,159,169,180,191,201,203,206,56,71,82,86,80,87,76,107,75,49,51,49,56,81,61,41,51,88,90,63,40,36,19,67,91,165,161,62,110,155,163,166,137,68,23,32,19,20,59,25,42,16,90,28},{44,28,96,40,99,27,17,28,17,22,19,15,43,66,84,88,94,94,102,107,106,107,107,111,115,110,112,103,109,112,115,122,131,140,157,162,179,190,199,201,203,57,69,79,76,76,77,77,99,151,55,47,46,41,69,77,48,39,76,90,78,39,42,28},{70,84,150,169,90,87,146,159,164,146,72,18,24,32,29,29,21,45,55,64,30,20,19,104,31,65,53,45,23,17,20,41,45,25,36,66,86,92,95,100,103,108,104,108,112,116,112,109,107,106,107,117,121,129,135,151,163,178,188,196,202,205,135,71},{76,78,75,67,70,72,191,129,52,33,50,46,85,67,39,52,85,81,62,38,43,62,93,131,168,132,71,133,154,161,157,57,66,22,24,37,26,25,22,65,38,52,19,43,42,43,48,77,65,17,24,19,12,49,65,17,35,73,91,96,100,103,103,108},{106,110,110,109,112,108,105,103,114,118,128,139,143,157,173,185,193,202,205,201,65,76,83,74,63,64,55,176,192,80,34,37,38,61,78,53,45,66,89,70,50,47,45,87,115,168,159,53,115,154,158,167,129,85,19,28,20,22,25,22,53,21,66,28},{67,29,38,39,108,63,25,22,18,18,39,66,78,17,43,79,92,97,100,104,105,105,110,108,111,107,106,109,101,112,120,126,139,146,156,173,187,194,200,201,208,57,75,79,69,70,55,54,124,204,158,66,23,46,33,69,76,50,51,83,77,59,37,31},{67,94,162,172,89,89,147,159,168,150,91,33,21,23,25,36,27,20,39,52,30,39,21,29,59,65,102,21,21,19,17,20,44,70,78,11,54,87,97,102,102,104,103,108,106,112,107,103,104,112,114,116,123,136,137,157,169,182,193,201,204,206,54,74},{84,69,63,49,33,53,194,186,146,41,27,41,49,75,60,47,63,92,71,46,47,65,75,138,176,130,68,134,157,158,160,76,64,24,19,21,29,27,24,45,29,18,24,17,38,46,45,120,50,22,24,17,16,32,52,90,75,10,74,93,100,102,104,107},{103,108,110,107,103,106,110,110,114,123,133,141,153,166,179,190,198,203,203,115,74,81,75,66,52,29,28,177,181,189,122,25,36,36,60,74,47,50,77,80,57,33,66,62,100,171,158,51,117,153,156,167,122,101,16,35,25,22,23,28,22,42,21,20},{15,42,20,57,152,71,25,19,22,14,17,45,75,82,37,36,93,103,99,107,103,105,108,110,106,110,101,108,108,117,124,127,137,147,165,180,190,198,199,203,198,67,80,76,60,49,34,15,146,190,178,192,57,27,48,41,78,61,50,63,93,63,41,39},{58,67,159,169,63,91,147,159,166,149,68,33,27,51,24,33,27,44,40,31,22,17,28,23,55,130,89,95,28,19,18,21,28,59,84,85,17,62,93,99,108,103,106,111,110,111,104,104,105,105,114,119,132,136,152,164,177,187,195,197,206,211,61,80},{81,69,55,31,18,60,200,134,203,168,33,34,47,54,85,53,57,77,73,49,28,43,40,138,175,104,66,131,159,158,155,77,61,15,22,30,28,24,21,37,33,29,14,24,22,60,127,56,110,14,13,13,14,17,42,72,84,76,20,92,102,100,100,104},{108,111,106,105,103,110,104,112,120,128,133,146,158,174,184,194,198,204,208,57,81,77,64,51,30,17,19,187,164,189,204,91,27,47,36,72,69,56,65,82,56,28,23,28,101,171,151,39,119,152,155,163,132,106,30,19,18,38,28,27,48,36,35,19},{35,23,70,132,90,47,15,28,23,19,11,22,59,78,83,23,59,95,103,105,103,107,107,110,107,102,104,102,111,122,128,134,141,159,169,185,193,198,201,206,93,72,75,62,45,30,17,25,107,185,146,208,170,46,31,53,54,83,61,61,73,71,34,22},{11,33,157,156,36,94,145,155,161,145,49,57,28,20,27,32,52,31,44,31,30,33,28,73,113,82,66,26,22,20,20,16,14,39,71,84,85,13,86,101,101,105,104,108,109,103,103,103,106,113,121,123,132,141,155,170,182,191,199,205,206,186,66,67},{58,45,32,24,33,78,173,137,198,202,97,35,49,44,66,68,61,63,78,55,28,14,12,143,165,98,62,136,154,154,155,106,58,13,17,18,45,27,27,40,41,19,29,31,71,98,96,75,36,22,35,20,17,18,27,52,85,88,42,59,98,98,101,106},{106,110,107,103,97,105,113,120,123,133,141,148,167,178,190,197,203,205,211,56,68,53,41,39,42,46,95,123,149,162,214,153,59,29,56,46,77,62,61,76,70,33,7,13,106,169,125,37,117,152,157,159,126,85,53,30,21,24,28,30,43,30,24,30},{38,65,104,62,39,48,22,28,18,20,21,15,46,75,83,86,16,87,96,97,105,111,105,102,101,101,103,109,114,122,129,138,150,162,178,189,196,201,203,210,47,63,51,47,50,60,73,102,136,130,123,209,200,100,49,51,57,58,75,71,68,74,48,27},{8,44,163,150,33,96,148,153,160,142,95,59,18,23,22,39,42,29,46,20,26,27,48,77,59,48,33,97,98,25,21,24,14,25,53,82,86,56,58,96,101,110,110,103,109,104,103,103,112,113,121,129,136,146,156,173,183,195,201,203,208,85,49,42},{56,67,74,93,114,135,128,105,181,215,157,70,43,65,37,71,65,65,79,68,30,10,19,140,162,58,63,137,155,158,150,102,51,13,28,29,22,37,28,52,20,27,22,32,43,102,29,48,28,70,12,17,18,16,19,40,77,83,90,24,89,98,104,110},{108,106,102,103,102,107,116,123,124,137,146,151,175,181,193,199,202,204,186,49,43,67,79,97,108,116,129,136,105,125,209,197,98,60,53,62,49,72,70,65,69,53,14,14,120,156,109,38,123,155,158,155,124,93,37,18,26,19,26,41,39,24,35,14},{31,23,103,30,26,27,70,87,30,20,19,17,24,53,80,92,57,59,97,104,105,109,105,108,101,103,110,113,117,126,135,144,152,169,181,191,196,202,203,208,76,72,73,97,108,120,122,121,133,120,111,189,212,151,75,58,66,43,70,67,57,75,69,30},{9,65,156,136,27,101,150,156,158,141,134,63,21,30,28,28,34,31,35,33,26,53,15,96,24,29,88,48,165,19,21,33,24,21,39,76,88,88,30,90,97,104,103,108,106,104,103,107,112,119,122,130,138,153,166,180,189,196,200,204,206,118,68,89},{103,119,128,124,122,124,123,115,133,218,195,91,71,54,65,48,76,69,64,68,57,12,23,145,155,59,68,141,154,158,146,112,36,22,31,35,25,27,45,35,41,44,17,26,36,24,63,100,31,140,102,28,30,24,19,22,61,84,90,50,66,97,103,106},{109,105,103,99,99,107,114,123,128,140,149,168,175,187,193,201,203,204,86,100,102,113,127,128,126,123,121,120,114,113,201,209,137,78,65,64,51,62,72,62,70,77,20,12,125,161,100,41,125,156,156,156,119,86,25,19,39,31,19,39,27,35,36,30},{44,35,20,151,100,46,101,70,21,27,33,23,17,48,75,91,86,44,91,102,106,112,103,102,105,100,108,115,123,129,136,147,157,171,185,191,195,202,205,139,120,114,123,129,126,124,121,110,115,113,127,173,215,188,82,68,55,63,46,83,70,65,66,55},{10,84,163,134,23,107,152,157,158,136,122,38,20,26,55,27,28,35,29,27,17,35,44,49,78,108,60,106,75,12,32,35,26,24,25,55,88,93,34,72,98,107,103,106,105,104,106,105,115,116,126,137,143,155,173,181,189,197,200,205,203,105,119,124},{126,128,124,121,118,114,110,133,173,208,202,114,75,67,64,54,64,71,63,66,72,12,35,145,154,24,76,145,160,159,153,122,28,31,17,18,47,28,40,31,22,19,30,50,62,66,73,89,114,22,25,37,23,31,37,16,49,75,90,83,57,95,102,102},{108,108,99,102,103,111,118,125,135,143,153,169,181,189,195,200,205,207,66,127,130,124,126,122,122,116,108,106,133,192,195,211,168,84,74,65,74,44,75,73,70,65,7,17,136,164,86,37,127,157,160,159,123,68,22,20,27,27,27,50,25,24,44,14},{16,57,63,76,100,108,20,14,15,31,34,92,21,30,60,88,95,22,77,95,102,103,107,98,100,105,108,116,123,131,143,154,166,179,186,197,199,203,207,10,120,130,121,125,120,121,120,109,108,112,199,191,212,196,92,81,68,68,62,59,78,66,64,72},{9,100,165,133,15,107,153,158,161,140,109,29,19,22,22,32,25,41,41,35,20,37,80,44,52,74,98,48,70,48,45,99,80,25,21,45,84,95,59,64,96,101,107,103,105,98,102,111,115,122,132,135,144,161,178,185,193,198,204,207,113,105,124,131},{123,120,119,120,117,108,104,192,199,202,208,148,80,71,68,74,56,70,79,69,66,6,57,158,149,15,74,146,156,153,146,108,38,19,20,26,35,27,61,24,21,27,19,29,28,21,132,112,72,47,35,82,91,89,32,30,28,64,88,87,31,84,99,97},{108,106,98,102,110,110,120,125,133,147,160,173,184,191,196,203,207,204,41,124,138,123,125,118,119,115,106,105,160,209,196,212,194,93,75,67,72,68,56,77,68,61,8,15,141,160,86,32,130,156,152,154,124,107,29,24,30,52,24,66,21,41,23,20},{22,65,22,105,100,85,81,142,118,70,30,57,30,20,41,90,88,27,70,90,95,103,105,98,100,108,109,118,128,133,143,150,171,179,191,197,203,205,213,5,115,132,122,120,122,119,118,107,104,109,207,196,208,206,139,87,60,73,79,61,72,80,66,54},{7,118,165,120,11,113,160,157,157,135,90,37,21,19,23,49,26,49,20,35,21,38,40,26,93,106,105,109,149,37,21,29,37,28,22,33,71,90,79,59,89,97,102,107,102,102,105,107,116,125,134,145,156,165,177,185,195,201,205,211,5,104,123,123},{125,120,119,120,114,106,98,192,204,202,212,193,96,69,67,80,73,63,77,73,56,8,66,162,143,11,81,149,158,160,152,105,28,25,22,16,19,70,65,18,52,31,19,8,31,90,85,123,119,140,29,37,30,29,32,35,28,44,90,82,15,74,92,101},{102,101,106,104,111,117,127,133,139,154,164,178,185,197,199,204,209,89,20,121,126,126,124,119,120,114,108,102,141,212,200,212,205,141,73,63,71,78,61,74,74,70,9,19,147,159,57,34,133,161,162,160,124,70,34,13,20,22,37,68,18,25,17,12},{32,37,100,47,122,145,113,150,94,33,31,26,25,23,38,84,90,45,63,88,99,100,102,100,104,108,114,122,133,136,151,162,173,182,191,198,202,208,196,5,110,137,127,123,120,123,114,112,103,95,205,206,206,210,191,79,62,64,84,66,62,74,80,58},{8,122,162,114,11,113,157,159,165,138,125,21,33,16,19,11,121,48,19,44,15,33,42,64,31,88,131,77,107,125,14,31,32,29,26,32,46,87,85,42,82,97,103,99,103,101,110,112,120,129,135,142,156,172,181,193,200,205,206,216,4,89,121,130},{126,124,118,119,113,106,101,176,212,200,213,207,139,64,55,74,82,60,74,73,79,6,82,158,141,7,83,144,158,159,151,100,57,19,27,20,30,19,106,24,16,28,20,27,62,72,37,109,109,41,141,14,55,41,25,28,36,32,69,88,13,74,96,95},{97,101,101,107,113,119,126,135,141,156,164,177,187,197,200,209,214,11,5,117,129,127,128,123,118,113,107,108,106,202,195,208,209,189,73,61,68,84,69,63,76,71,7,44,149,156,46,42,132,156,156,159,120,100,30,34,19,15,20,115,15,38,34,27},{28,55,94,52,126,141,30,119,27,23,39,32,24,40,20,57,70,54,65,92,92,101,102,101,105,115,115,126,130,142,150,162,173,183,194,201,205,215,31,9,121,127,127,128,121,119,110,112,108,100,173,195,200,210,205,138,60,57,77,85,63,74,72,81},{21,136,164,105,13,115,156,157,159,138,101,23,20,34,24,28,22,56,56,29,38,37,38,81,52,85,118,61,21,148,20,38,28,31,40,18,28,72,79,26,80,94,97,103,102,107,106,112,126,131,143,149,161,169,181,193,196,203,212,133,7,46,113,130},{124,126,123,120,115,110,103,111,181,193,211,208,189,64,62,69,81,67,62,77,77,13,96,163,144,12,87,140,158,160,148,99,113,26,23,26,25,21,126,28,12,24,68,53,71,74,53,141,131,56,167,12,48,64,22,25,23,29,64,62,17,70,92,90},{100,102,105,110,115,118,128,136,152,160,169,177,188,198,202,211,201,16,6,132,132,128,122,124,119,114,115,107,97,141,183,203,208,200,137,59,61,72,80,61,68,70,7,52,158,150,56,43,131,159,153,156,120,145,19,18,37,22,17,43,16,23,16,58},{24,59,93,68,121,144,41,142,32,15,32,25,25,34,26,27,73,40,58,81,88,99,102,107,107,117,117,126,137,148,155,163,174,185,194,201,209,216,14,15,120,119,125,127,125,122,116,119,115,103,102,157,192,210,206,191,57,65,66,80,66,58,74,74}};
int i = 64;
int j = 64;
for(i=0; i <64 ; i++){
	for(j=0; j<64;j++){
		printf("%d",tab_lena[i][j]);
		if(j+1 < 64 || i+1 < 64) printf(",");
	}
}
return 0;
}
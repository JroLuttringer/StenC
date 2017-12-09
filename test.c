int main () {
    int i;
    int j;
    int abs_gx;
    int abs_gy;
    //int image[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
   // int image[35][35] = { { 79 , 70 , 78 , 75 , 91 , 63 , 74 , 99 , 73 , 51 , 55 , 63 , 51 , 48 , 50 , 80 , 69 , 47 , 43 , 51 , 68 , 68 , 52 , 55 , 55 , 67 , 83 , 79 , 166 , 255 , 249 , 255 , 255 , 250 , 255 } , { 75 , 89 , 62 , 71 , 83 , 170 , 150 , 174 , 38 , 42 , 84 , 58 , 77 , 77 , 58 , 56 , 55 , 73 , 58 , 60 , 52 , 44 , 55 , 48 , 53 , 70 , 93 , 89 , 122 , 255 , 255 , 240 , 251 , 252 , 255 } , { 63 , 92 , 83 , 65 , 73 , 160 , 162 , 73 , 34 , 62 , 96 , 87 , 92 , 47 , 44 , 47 , 67 , 80 , 77 , 73 , 45 , 31 , 37 , 52 , 60 , 61 , 60 , 91 , 94 , 203 , 239 , 225 , 255 , 255 , 250 } , { 70 , 105 , 108 , 64 , 77 , 168 , 147 , 24 , 44 , 59 , 98 , 133 , 64 , 38 , 77 , 63 , 51 , 54 , 52 , 42 , 38 , 47 , 42 , 32 , 46 , 53 , 75 , 79 , 65 , 127 , 162 , 196 , 248 , 255 , 255 } , { 104 , 118 , 103 , 61 , 74 , 145 , 143 , 14 , 36 , 75 , 105 , 116 , 39 , 66 , 74 , 53 , 51 , 63 , 60 , 62 , 44 , 21 , 45 , 45 , 30 , 39 , 43 , 74 , 71 , 70 , 108 , 134 , 255 , 248 , 249 } , { 120 , 147 , 114 , 63 , 71 , 144 , 65 , 46 , 36 , 71 , 95 , 116 , 55 , 75 , 91 , 62 , 64 , 42 , 46 , 65 , 51 , 25 , 34 , 56 , 38 , 27 , 53 , 81 , 60 , 56 , 72 , 114 , 218 , 254 , 251 } , { 123 , 147 , 123 , 62 , 74 , 76 , 46 , 34 , 38 , 74 , 79 , 122 , 103 , 69 , 80 , 86 , 98 , 87 , 96 , 73 , 34 , 45 , 26 , 38 , 64 , 67 , 59 , 65 , 53 , 66 , 80 , 75 , 129 , 243 , 255 } , { 70 , 104 , 86 , 53 , 70 , 53 , 42 , 25 , 41 , 59 , 100 , 152 , 149 , 132 , 127 , 136 , 143 , 143 , 121 , 98 , 45 , 63 , 39 , 28 , 55 , 55 , 55 , 44 , 49 , 53 , 58 , 70 , 140 , 195 , 207 } , { 146 , 159 , 158 , 150 , 87 , 64 , 29 , 24 , 25 , 60 , 118 , 177 , 163 , 175 , 164 , 173 , 162 , 160 , 157 , 109 , 57 , 65 , 67 , 27 , 39 , 36 , 44 , 58 , 61 , 53 , 53 , 62 , 75 , 131 , 154 } , { 100 , 103 , 99 , 101 , 84 , 47 , 16 , 18 , 35 , 85 , 138 , 178 , 173 , 169 , 174 , 171 , 182 , 173 , 172 , 146 , 76 , 74 , 58 , 54 , 37 , 43 , 44 , 39 , 42 , 52 , 59 , 60 , 65 , 100 , 118 } , { 52 , 57 , 64 , 61 , 39 , 34 , 37 , 34 , 23 , 102 , 154 , 183 , 181 , 175 , 190 , 182 , 176 , 187 , 185 , 183 , 144 , 87 , 79 , 41 , 27 , 29 , 40 , 52 , 52 , 44 , 43 , 49 , 50 , 74 , 114 } , { 62 , 71 , 62 , 76 , 35 , 34 , 31 , 20 , 25 , 119 , 174 , 203 , 198 , 201 , 197 , 182 , 179 , 183 , 184 , 201 , 195 , 175 , 101 , 36 , 33 , 37 , 37 , 32 , 30 , 37 , 48 , 56 , 73 , 80 , 126 } , { 64 , 74 , 73 , 72 , 31 , 41 , 34 , 35 , 12 , 101 , 187 , 216 , 219 , 227 , 209 , 195 , 187 , 187 , 187 , 184 , 171 , 158 , 89 , 48 , 25 , 30 , 36 , 37 , 35 , 35 , 43 , 52 , 58 , 56 , 104 } , { 65 , 67 , 77 , 81 , 61 , 29 , 34 , 30 , 17 , 90 , 205 , 214 , 205 , 193 , 185 , 185 , 176 , 181 , 172 , 142 , 109 , 67 , 59 , 58 , 40 , 28 , 27 , 37 , 36 , 28 , 38 , 59 , 48 , 52 , 105 } , { 150 , 22 , 80 , 73 , 50 , 43 , 42 , 25 , 18 , 60 , 170 , 171 , 149 , 132 , 144 , 159 , 161 , 161 , 147 , 118 , 77 , 86 , 64 , 81 , 53 , 49 , 39 , 28 , 28 , 37 , 43 , 44 , 39 , 44 , 81 } , { 206 , 193 , 118 , 70 , 112 , 62 , 67 , 27 , 25 , 29 , 101 , 109 , 80 , 74 , 85 , 98 , 145 , 175 , 154 , 116 , 94 , 100 , 115 , 95 , 74 , 59 , 43 , 36 , 36 , 35 , 35 , 35 , 39 , 47 , 78 } , { 252 , 228 , 88 , 77 , 58 , 39 , 59 , 48 , 22 , 15 , 87 , 67 , 88 , 96 , 93 , 95 , 134 , 221 , 200 , 134 , 155 , 143 , 139 , 134 , 102 , 61 , 34 , 39 , 34 , 30 , 43 , 38 , 35 , 41 , 70 } , { 249 , 255 , 113 , 40 , 93 , 40 , 27 , 24 , 24 , 18 , 84 , 117 , 124 , 123 , 130 , 146 , 165 , 220 , 232 , 201 , 185 , 192 , 195 , 164 , 123 , 75 , 40 , 36 , 37 , 37 , 53 , 49 , 35 , 70 , 91 } , { 252 , 250 , 96 , 63 , 101 , 41 , 32 , 25 , 20 , 14 , 69 , 154 , 168 , 166 , 180 , 179 , 187 , 234 , 251 , 229 , 187 , 168 , 189 , 170 , 142 , 89 , 45 , 32 , 40 , 43 , 56 , 48 , 41 , 56 , 152 } , { 244 , 255 , 91 , 75 , 108 , 27 , 30 , 31 , 28 , 23 , 58 , 169 , 202 , 197 , 196 , 149 , 172 , 232 , 240 , 245 , 244 , 144 , 129 , 149 , 134 , 101 , 71 , 45 , 40 , 34 , 47 , 51 , 44 , 68 , 166 } , { 199 , 255 , 103 , 55 , 48 , 38 , 36 , 20 , 28 , 20 , 31 , 158 , 197 , 192 , 172 , 117 , 191 , 203 , 222 , 208 , 173 , 131 , 133 , 116 , 123 , 104 , 79 , 48 , 38 , 31 , 35 , 42 , 46 , 71 , 120 } , { 195 , 244 , 128 , 148 , 168 , 15 , 33 , 32 , 35 , 22 , 8 , 118 , 156 , 160 , 138 , 124 , 121 , 136 , 161 , 139 , 128 , 174 , 136 , 111 , 122 , 113 , 87 , 53 , 37 , 35 , 34 , 48 , 58 , 104 , 177 } , { 185 , 196 , 153 , 153 , 111 , 51 , 38 , 17 , 48 , 39 , 18 , 63 , 124 , 141 , 127 , 126 , 149 , 142 , 135 , 130 , 141 , 168 , 99 , 111 , 126 , 133 , 108 , 66 , 33 , 35 , 40 , 72 , 49 , 116 , 246 } , { 104 , 113 , 105 , 212 , 168 , 82 , 49 , 42 , 23 , 29 , 25 , 13 , 114 , 145 , 136 , 114 , 64 , 149 , 162 , 168 , 201 , 174 , 98 , 145 , 137 , 133 , 92 , 54 , 31 , 44 , 36 , 60 , 55 , 186 , 252 } , { 65 , 15 , 102 , 255 , 157 , 51 , 44 , 53 , 21 , 37 , 35 , 25 , 44 , 125 , 147 , 144 , 116 , 104 , 162 , 161 , 161 , 138 , 136 , 154 , 148 , 146 , 84 , 39 , 61 , 42 , 44 , 52 , 93 , 220 , 250 } , { 49 , 98 , 252 , 235 , 185 , 34 , 37 , 39 , 30 , 28 , 50 , 27 , 50 , 57 , 124 , 143 , 145 , 127 , 116 , 109 , 126 , 138 , 155 , 163 , 160 , 152 , 136 , 117 , 89 , 54 , 87 , 159 , 195 , 237 , 250 } , { 92 , 248 , 250 , 241 , 157 , 26 , 51 , 28 , 26 , 57 , 64 , 33 , 33 , 60 , 71 , 82 , 155 , 142 , 146 , 146 , 145 , 179 , 181 , 172 , 160 , 154 , 139 , 115 , 109 , 91 , 168 , 218 , 223 , 214 , 242 } , { 222 , 255 , 227 , 207 , 170 , 65 , 70 , 72 , 53 , 67 , 85 , 37 , 50 , 66 , 36 , 69 , 92 , 154 , 165 , 174 , 181 , 196 , 182 , 152 , 146 , 134 , 125 , 115 , 131 , 79 , 178 , 219 , 191 , 198 , 247 } , { 248 , 247 , 227 , 200 , 172 , 93 , 84 , 87 , 60 , 55 , 97 , 73 , 66 , 64 , 38 , 95 , 93 , 81 , 125 , 154 , 157 , 162 , 140 , 150 , 141 , 116 , 125 , 118 , 126 , 94 , 138 , 203 , 175 , 208 , 241 } , { 255 , 247 , 234 , 209 , 205 , 151 , 110 , 105 , 82 , 50 , 109 , 89 , 92 , 65 , 80 , 93 , 96 , 106 , 104 , 113 , 137 , 140 , 135 , 141 , 127 , 123 , 121 , 117 , 129 , 101 , 44 , 202 , 173 , 217 , 230 } , { 245 , 246 , 224 , 224 , 197 , 145 , 115 , 150 , 131 , 73 , 96 , 108 , 100 , 94 , 92 , 109 , 118 , 114 , 121 , 123 , 127 , 136 , 131 , 134 , 133 , 117 , 124 , 128 , 115 , 122 , 80 , 87 , 185 , 225 , 240 } , { 252 , 254 , 224 , 174 , 164 , 144 , 119 , 101 , 124 , 79 , 115 , 97 , 114 , 107 , 88 , 113 , 114 , 133 , 115 , 121 , 125 , 128 , 132 , 129 , 121 , 132 , 120 , 127 , 135 , 108 , 146 , 59 , 197 , 225 , 243 } , { 245 , 249 , 237 , 230 , 187 , 148 , 126 , 102 , 86 , 112 , 128 , 109 , 110 , 108 , 99 , 119 , 118 , 126 , 123 , 117 , 113 , 117 , 127 , 128 , 127 , 120 , 131 , 128 , 131 , 110 , 159 , 188 , 194 , 226 , 228 } , { 246 , 246 , 239 , 233 , 198 , 163 , 133 , 109 , 85 , 119 , 139 , 119 , 122 , 111 , 108 , 122 , 119 , 127 , 124 , 119 , 115 , 117 , 125 , 124 , 120 , 116 , 125 , 128 , 131 , 115 , 155 , 177 , 205 , 235 , 232 } , { 246 , 241 , 241 , 236 , 209 , 181 , 139 , 116 , 86 , 129 , 150 , 127 , 132 , 112 , 119 , 125 , 120 , 127 , 125 , 121 , 118 , 118 , 123 , 119 , 117 , 116 , 121 , 130 , 132 , 124 , 155 , 171 , 210 , 238 , 233 } };
    int image[16][16]= {
    {1,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {2,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {3,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {4,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {5,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {6,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {7,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {8,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {9,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {10,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {11,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {12,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {13,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {14,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {15,2,3,4,5,6,7,8,9,10,11,12,13,15,16},
    {16,2,3,4,5,6,7,8,9,10,11,12,13,15,16}
    };
   /* int sobel[64][64];
    stencil gx{1,2} = { {1,0,-1}, {2,0,-2}, {1,0,-1} };
    stencil gy{1,2} = { {1,2,1}, {0,0,0}, {-1,-2,-1}};*/

/*
    //Filtre Sobel
    for(i=1; i < 64-1; i++){
        for(j=1; j<64-1;j++){
            abs_gx = image[i][j] $ gx;
            abs_gy = image[i][j] $ gy;
            if(abs_gx < 0) {abs_gx = -abs_gx;}
            if(abs_gy < 0) {abs_gy = -abs_gy;}
            sobel[i][j] = abs_gx+abs_gy/2;

        }
    }

    for(i=1; i < 64-1; i++){
        for(j=1; j<64-1;j++){
            printi(sobel[i][j]);
            if(j+1 < 64 -1) {printf(",");}    
        }
    }

*/

    return 0;
}
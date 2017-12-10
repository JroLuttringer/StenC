#define WIDTH 64
#define HEIGHT 64
int main () {
  
    int image[64][64] = { { 134 , 131 , 130 , 130 , 134 , 136 , 135 , 142 , 150 , 141 , 113 , 74 , 55 , 58 , 59 , 58 , 64 , 67 , 67 , 65 , 63 , 65 , 67 , 71 , 73 , 75 , 75 , 73 , 72 , 71 , 68 , 69 , 66 , 65 , 70 , 66 , 58 , 48 , 47 , 51 , 51 , 47 , 41 , 32 , 28 , 26 , 24 , 22 , 21 , 56 , 121 , 116 , 54 , 22 , 14 , 10 , 10 , 7 , 4 , 42 , 66 , 44 , 29 , 22 } , { 132 , 130 , 131 , 132 , 134 , 139 , 145 , 142 , 123 , 89 , 59 , 52 , 58 , 61 , 58 , 61 , 66 , 65 , 65 , 64 , 61 , 64 , 66 , 66 , 68 , 70 , 69 , 71 , 70 , 67 , 66 , 69 , 65 , 62 , 64 , 58 , 50 , 44 , 45 , 45 , 44 , 43 , 38 , 33 , 29 , 22 , 21 , 21 , 16 , 27 , 87 , 138 , 148 , 138 , 125 , 116 , 101 , 87 , 79 , 90 , 110 , 91 , 63 , 51 } , { 132 , 128 , 129 , 134 , 141 , 142 , 128 , 98 , 61 , 45 , 50 , 54 , 54 , 56 , 52 , 57 , 62 , 63 , 64 , 62 , 61 , 64 , 67 , 66 , 66 , 64 , 60 , 61 , 61 , 59 , 59 , 60 , 53 , 48 , 46 , 39 , 34 , 31 , 28 , 21 , 29 , 36 , 34 , 34 , 37 , 40 , 53 , 50 , 34 , 25 , 40 , 86 , 125 , 139 , 144 , 151 , 155 , 157 , 169 , 174 , 172 , 161 , 174 , 184 } , { 127 , 129 , 132 , 139 , 146 , 132 , 109 , 93 , 85 , 88 , 90 , 89 , 87 , 87 , 86 , 83 , 84 , 87 , 89 , 88 , 89 , 91 , 94, 94 , 92 , 88 , 82 , 81 , 81 , 80 , 79 , 77 , 72 , 67 , 64 , 58 , 55 , 53 , 50 , 44 , 60 , 82 , 84 , 83 , 88 , 82 , 85 , 89 , 80 , 53 , 33 , 33 , 39 , 34 , 33 , 40 , 51 , 63 , 75 , 95 , 109, 115 , 146 , 169 } , { 134 , 138 , 143 , 144 , 140 , 133 , 131 , 136 , 140 , 139 , 138 , 134 , 132 , 132 , 132 , 133 , 132 , 132 , 136 , 137 , 138 , 137 , 140 , 139 , 139 , 137 , 136 , 136 , 135 , 135 , 135 , 134 , 136 , 135 , 135 , 133 , 133 , 132 , 131 , 130 , 132 , 136 , 138 , 138 , 141 , 135 , 128 , 131 , 132 , 123 , 115 , 117 , 116 , 115 , 113 , 110 , 107 , 102 , 95 , 95 ,96 , 97 , 100 , 106 } , { 148 , 149 , 143 , 136 , 134 , 137 , 139 , 143 , 144 , 145 , 146 , 145 , 144 , 141 , 141 , 145 , 147 , 149 , 153 , 153 , 151 , 152 , 154 , 152 , 151 , 152 , 154 , 153 , 154 , 155 , 156 , 156 , 158 , 160 , 162 , 162 , 161 , 158 , 154 , 155 , 152 , 149 , 150 , 155 , 159 , 160 , 157 , 156 , 153 , 150 , 150 , 156 , 159 , 161 , 161 , 160 , 160 , 157 , 155 , 156 , 156 , 155 , 153 , 154 } , { 145 , 137 , 134 , 134 , 134 , 133 , 136 , 137 , 135 , 133 , 134 , 134 , 133 , 133 , 136 , 135 , 140 , 146 , 148 , 146 , 146 , 148 , 149 , 148 , 147 , 149 , 151 , 151 , 153 , 154 , 155 , 155 , 155 , 158 , 162 , 163 , 161 , 158 , 155 , 157 , 157 , 157 , 159 , 160 , 161 , 161 , 161 , 160 , 156 , 152 , 153 , 153 , 158 , 160 , 162 , 159 , 161 , 160 , 161 , 165 , 167 , 168 , 169 , 167 } , { 99 , 94 , 96 , 95 , 94 , 93 , 94 , 93 , 90 , 89 , 88 , 87 , 90 , 90 , 90 , 88 , 91 , 95 , 96 , 96 , 98 , 100 , 99 , 101 , 103 , 103 , 104 , 106 , 108 , 106 , 107 , 109 , 109 , 108 , 112 , 115 , 115 , 114 , 112 , 114 , 116 , 119 , 122 , 119 , 123 , 124 , 119 , 120 , 116 , 135 , 126 , 138 , 134 , 132 , 134 , 134 , 137 , 136 , 133 , 131 , 129 ,132 , 122 , 115 } , { 62 , 58 , 59 , 56 , 55 , 53 , 52 , 48 , 46 , 45 , 46 , 47 , 48 , 48 , 45 , 42 , 46 , 47 , 46 , 47 , 47 , 45 , 44 , 45 , 45 , 44 , 44 , 44 , 48 , 49 , 48 , 49 , 47 , 48 , 53 , 52 , 51 , 51 , 48 , 51 , 56 , 51 , 49 , 58 , 72 , 51 , 49 , 45 , 87 , 83 , 93 , 111 , 81 , 76 , 64 , 62 , 68 , 77 , 68 , 65 , 62 , 43 , 32 , 27 } , { 71 , 66 , 66 , 66 , 66 , 64 , 63 ,59 , 57 , 57 , 58 , 61 , 59 , 57 , 54 , 53 , 58 , 59 , 58 , 59 , 59 , 58 , 56 , 56 , 56 , 55 , 51 , 54 , 55 , 58 , 56 , 57 , 54 , 56 , 64 , 62 , 60 , 63 , 74 , 76 , 62 , 58 , 66 , 74 , 72 , 82 , 71 , 60 , 78 , 57 , 45 , 21 , 15 , 22 , 22 , 18 , 17 , 21 , 27 , 24 , 21 , 22 , 24 , 25 } , { 75 , 73 , 75 , 74 , 72 , 71 , 71 , 66 , 67 , 68 , 65 , 65 , 66 , 67 , 62 , 66 , 67 , 68 , 66, 66 , 65 , 64 , 65 , 64 , 63 , 62 , 63 , 65 , 68 , 69 , 69 , 69 , 66 , 67 , 78 , 74 , 88 , 82 , 98 , 87 , 73 , 81 , 84 , 77 , 80 , 59 , 57 , 43 , 39 , 26 , 13 , 23 , 31 , 29 , 22 , 21 , 26 , 31 , 21 , 26 , 26 , 30 , 30 , 37 } , { 75 , 71 , 71 , 71 , 71 , 70 , 70 , 68 , 66 , 68 , 69 , 68 , 66 , 68 , 65 , 65 , 69 , 67 , 63 , 65 , 64 , 63 , 65 , 65 , 65 , 63 , 64 , 65 , 70 , 70 , 69 , 69 , 64 , 65 , 62 , 96 , 102 , 82 , 71 , 58 , 57 , 46 , 56 , 44 , 44 , 56 , 42 , 47 , 42 , 40 , 55 , 41 , 30 , 20 , 21 , 31 , 35 , 26 , 29 , 28 , 27 , 32 , 38 , 41 } , { 75 , 72 , 70 , 70 , 70 , 70 , 71 , 71 , 69 , 68 , 69 , 69 , 68 , 69 , 69 , 67 , 67 , 68 , 65 , 65 , 65 , 64 , 65 , 65 , 64 , 63 , 63 , 64 , 65 , 68 , 68 , 66 , 56 , 45 , 72 , 110 , 85 , 66 , 77 , 67 , 61 , 55 , 61 , 43 , 30 , 34 , 33 , 33 , 35 , 36 , 53 , 47 , 29 , 46 , 65 , 46 , 30 , 33 , 34 , 28 , 25 , 33 , 35 , 46 } , { 82 , 82 , 80 , 79 , 78 , 79 , 79 , 77 , 75 , 76 , 75 , 74 , 75 , 73 , 74 , 72 , 75 , 72 , 68 , 65 , 61 , 57 , 58 , 62 , 66 , 68 , 68 , 71 , 76 , 76 , 74 , 69 , 100 , 104 , 118 , 66 , 52 , 57 , 60 , 56 , 59 , 51 , 36 , 38 , 47 , 53 , 42 , 37 , 25 , 44 , 63 , 41 , 55 , 59 , 47 , 40 , 34 , 39 , 36 , 35 , 36 , 41 , 44 , 60 } , { 91 , 89 , 88 , 88 , 87 , 87 , 86 , 84 , 81 , 81 , 81 , 82 , 83 , 80 , 75 , 70 , 74 , 74 , 78 , 80 , 84 , 88 , 78 , 61 , 55 , 65 , 76 , 79 , 87 , 82 , 81 , 86 , 124 , 162 , 117 , 26 , 40 , 51 , 59 , 62 , 56 , 50 , 45 , 65 , 87 , 103 , 96 , 79 , 101 , 68 , 42 , 40 , 23 , 24 , 29 , 30 , 32 , 32 , 34 , 35 , 44 , 50 , 39 ,43 } , { 95 , 94 , 93 , 92 , 90 , 90 , 90 , 88 , 83 , 83 , 85 , 85 , 83 , 84 , 97 , 128 , 142 , 151 , 169 , 173 , 171 , 185 , 191 , 180 , 142 , 89 , 62 , 65 , 73 , 79 , 96 , 121 , 127 , 99 ,44 , 43 , 83 , 81 , 95 , 94 , 84 , 83 , 58 , 68 , 74 , 84 , 103 , 62 , 66 , 89 , 76 , 53 , 42 , 34 , 25 , 24 , 30 , 27 , 23 , 23 , 34 , 61 , 78 , 64 } , { 98 , 96 , 96 , 96 , 93 , 91 , 92 , 89 , 88 , 86 , 87 , 86 , 90 , 106 , 120 , 115 , 103 , 95 , 106 , 124 , 134 , 148 , 160 , 169 , 188 , 186 , 158 , 153 , 118 , 91 , 82 , 85 , 105 , 36 , 58 , 88 , 72 , 48 , 59 , 61 , 93 , 102 ,75 , 58 , 72 , 72 , 90 , 103 , 69 , 88 , 79 , 48 , 54 , 42 , 24 , 31 , 34 , 34 , 28 , 26 , 34 , 39 , 53 , 66 } , { 99 , 98 , 97 , 96 , 95 , 92 , 93 , 91 , 89 , 86 , 88 , 90 , 83 , 71 , 65 , 64 , 63 , 67 , 73 , 92 , 105 , 122 , 109 , 103 , 132 , 154 , 178 , 155 , 130 , 107 , 74 , 63 , 45 , 37 , 48 , 44 , 20 , 23 , 24 , 27 , 30 , 54 , 98 , 81 , 65 , 94 , 83 , 105 , 103 , 88 , 66 ,54 , 58 , 69 , 53 , 38 , 46 , 58 , 54 , 27 , 40 , 46 , 47 , 54 } , { 98 , 99 , 100 , 96 , 93 , 92 , 95 , 92 , 89 , 95 , 87 , 77 , 79 , 76 , 77 , 77 , 73 , 69 , 72 , 68 , 72 , 88 , 94 , 100 ,95 , 96 , 94 , 75 , 74 , 91 , 107 , 74 , 43 , 41 , 42 , 38 , 33 , 23 , 18 , 17 , 36 , 64 , 46 , 65 , 99 , 105 , 82 , 98 , 117 , 86 , 98 , 94 , 73 , 67 , 71 , 58 , 63 , 59 , 102 , 70 , 42 , 51 , 48 , 38 } , { 102 , 98 , 98 , 97 , 94 , 94 , 94 , 93 , 97 , 89 , 76 , 78 , 81 , 80 , 78 , 81 , 83 , 78 , 77 , 74 , 77 , 91 , 83 , 80 , 94 , 93 , 84 , 87 , 93 , 96 , 66 , 44 , 59 , 48 , 62, 73 , 68 , 33 , 41 , 55 , 30 , 30 , 44 , 139 , 141 , 137 , 136 , 69 , 96 , 92 , 112 , 120 , 108 , 100 , 101 , 113 , 100 , 52 , 60 , 110 , 82 , 87 , 66 , 42 } , { 102 , 100 , 99 , 97 , 95 , 93 , 91 , 99 , 89 , 76 , 82 , 87 , 83 , 84 , 87 , 92 , 89 , 86 , 84 , 86 , 104 , 100 , 89 , 100 , 96 , 91 , 93 , 90 , 82 , 47 , 36 , 46 , 64 , 77 , 94 , 96 , 71 , 27 , 52 , 77 , 55 , 57 , 123, 161 , 129 , 124 , 60 , 27 , 54 , 109 , 80 , 88 , 109 , 105 , 115 , 86 , 82 , 58 , 58 , 76 , 65 , 56 , 62 , 62 } , { 102 , 101 , 99 , 97 , 96 , 94 , 95 , 109 , 93 , 85 , 90 , 83 , 86 , 92 ,97 , 94 , 91 , 88 , 90 , 107 , 103 , 97 , 106 , 98 , 90 , 93 , 96 , 90 , 44 , 35 , 47 , 53 , 36 , 26 , 47 , 54 , 71 , 88 , 104 , 50 , 16 , 107 , 137 , 96 , 90 , 39 , 19 , 28 , 23 , 42 , 68 ,91 , 78 , 68 , 115 , 76 , 63 , 96 , 37 , 22 , 22 , 20 , 18 , 43 } , { 101 , 101 , 99 , 94 , 95 , 95 , 95 , 97 , 94 , 94 , 88 , 87 , 97 , 104 , 104 , 97 , 94 , 91 , 115 , 112 , 99 , 107 , 101, 96 , 95 , 95 , 90 , 53 , 28 , 26 , 28 , 31 , 41 , 31 , 16 , 16 , 28 , 58 , 56 , 20 , 60 , 102 , 89 , 58 , 27 , 27 , 30 , 32 , 39 , 32 , 31 , 45 , 78 , 89 , 81 , 62 , 32 , 35 , 23 , 20 , 18, 18 , 20 , 36 } , { 101 , 99 , 99 , 97 , 97 , 92 , 99 , 107 , 103 , 99 , 94 , 98 , 106 , 111 , 106 , 97 , 90 , 118 , 117 , 104 , 114 , 105 , 98 , 102 , 98 , 91 , 61 , 33 , 35 , 39 , 41 , 33, 23 , 34 , 24 , 21 , 16 , 9 , 25 , 90 , 168 , 115 , 44 , 23 , 21 , 27 , 26 , 30 , 31 , 34 , 33 , 32 , 21 , 24 , 30 , 58 , 37 , 22 , 20 , 15 , 18 , 21 , 43 , 65 } , { 103 , 99 , 97 , 101 , 95 , 93 , 116 , 115 , 106 , 105 , 104 , 108 , 111 , 111 , 101 , 88 , 124 , 124 , 112 , 121 , 112 , 103 , 104 , 106 , 92 , 56 , 40 , 20 , 25 , 33 , 24 , 30 , 47 , 20 , 17 , 18 , 41 , 73 , 125 ,145 , 95 , 27 , 19 , 24 , 24 , 27 , 26 , 26 , 27 , 27 , 29 , 33 , 31 , 38 , 31 , 53 , 42 , 20 , 14 , 23 , 45 , 38 , 70 , 80 } , { 103 , 98 , 101 , 92 , 91 , 94 , 123 , 121 , 111 , 107 , 107 , 114 , 115 , 108 , 90 , 130 , 143 , 124 , 125 , 121 , 118 , 115 , 108 , 98 , 77 , 52 , 52 , 40 , 26 , 27 , 32 , 24 , 24 , 20 , 23 , 70 , 121 , 175 , 150 , 54 , 10 , 28 , 31 , 33 , 32 , 36 , 27 , 24 , 25 , 25 , 28 , 29 , 26 , 25 , 29 , 30 , 24 , 23 , 40 , 64 , 64 , 47 , 82 , 86 } , { 103 , 100 , 98 , 90 , 87 , 98 , 134 , 134 , 119 , 114 , 111 , 114 , 110 , 94 , 122 , 158 , 144 , 143 , 136 , 123 , 122 , 119 , 105 , 90 , 52 , 34 , 29 , 43 , 33 , 31 , 40 , 37 , 18 , 54 , 112 , 157 , 179 , 103 , 20 , 14 , 26 , 32 , 28 , 27 , 31 , 34 , 29 , 28 , 24 , 24 , 29 , 35 , 33 , 29 , 24 , 26 , 40 , 58 , 80 , 85 , 44 , 70 , 89 , 92 } , { 100 , 98 , 98 , 93 , 87 , 108 , 155 , 145 , 136 , 126 , 121 , 119 , 110 , 117 , 166 , 154 , 155 , 156 , 148 , 137 , 132 , 109 , 96 , 72 , 38 , 41 , 50 , 44 , 55 , 38 , 30 , 44 , 103 , 142 , 175 , 167 , 70 , 25 , 36 , 48 , 58 , 68 , 66 , 55 , 47 , 41 , 32 , 31 , 32 , 30 , 31 , 34 , 27 , 30 , 49 , 70 , 82 , 92 , 81 , 42 , 50, 90 , 92 , 93 } , { 102 , 98 , 99 , 94 , 86 , 116 , 169 , 158 , 155 , 150 , 145 , 139 , 128 , 162 , 172 , 160 , 165 , 155 , 148 , 146 , 138 , 101 , 73 , 51 , 23 , 30 , 37 , 60 , 53 , 39 , 63 , 129 , 165 , 184 , 162 , 74 , 64 , 80 , 75 , 73 , 73 , 77 , 76 , 68 , 60 , 45 , 36 , 35 , 31 , 28 , 36 , 53 , 68 , 70 , 86 , 91 , 86 , 66 , 42 , 60 , 92 , 94 , 94 , 94 } , { 99 , 99 , 98 ,94 , 86 , 110 , 168 , 164 , 166 , 167 , 170 , 154 , 159 , 184 , 169 , 167 , 168 , 159 , 149 , 151 , 139 , 101 , 61 , 42 , 51 , 39 , 24 , 13 , 29 , 92 , 138 , 172 , 191 , 168 , 91 , 91 , 97 ,95 , 94 , 91 , 89 , 89 , 89 , 91 , 83 , 68 , 45 , 30 , 37 , 36 , 36 , 39 , 42 , 45 , 51 , 52 , 53 , 63 , 88 , 101 , 100 , 97 , 96 , 97 } , { 103 , 101 , 103 , 97 , 92 , 98 , 165 , 174 , 174 , 175 , 173 , 163 , 187 , 181 , 172 , 176 , 169 , 154 , 155 , 150 , 136 , 119 , 111 , 74 , 51 , 32 , 28 , 31 , 103 , 138 , 151 , 167 , 139 , 73 , 100 , 121 , 121 , 111 , 106 , 102 , 99 , 98 ,97 , 93 , 88 , 81 , 68 , 31 , 49 , 78 , 75 , 74 , 68 , 70 , 73 , 81 , 94 , 102 , 102 , 104 , 104 , 103 , 101 , 99 } , { 101 , 99 , 101 , 99 , 98 , 90 , 151 , 184 , 178 , 181 , 171 , 185 , 194 , 180 , 184 , 178 , 163 , 160 , 159 , 152 , 141 , 114 , 86 , 60 , 60 , 51 , 42 , 91 , 156 , 168 , 169 , 151 , 41 , 29 , 95 , 129 , 143 , 133 , 123 , 114 , 112 , 108 , 104 , 103 , 97 , 92 , 88 , 63 , 67 , 95 , 88 , 89 , 95 , 96 , 99 , 100 , 105 , 107 , 106 , 105 , 106 , 104 , 102 , 101 } , { 102 , 99 , 99 , 98 , 100 , 88 , 116 , 189 , 184 , 183 , 182 , 200 , 191 , 185 , 188 , 178 , 170 , 167 , 156 , 147 , 141 , 131 , 69 , 60 , 44 , 67 , 85 , 125 , 144 , 160 , 168 , 100 , 23 , 44 , 83 , 123 , 153 , 154 , 137 , 124 , 118 , 114 , 105 , 106 , 111 , 103 , 100 , 86 , 84 ,98 , 93 , 99 , 100 , 100 , 103 , 105 , 107 , 110 , 108 , 107 , 106 , 107 , 106 , 103 } , { 100 , 97 , 99 , 95 , 95 , 93 , 86 , 152 , 195 , 185 , 194 , 199 , 190 , 195 , 189 , 181 , 181 , 168, 162 , 148 , 146 , 133 , 65 , 39 , 54 , 98 , 140 , 169 , 165 , 162 , 108 , 88 , 31 , 72 , 113 , 119 , 154 , 155 , 146 , 133 , 126 , 125 , 115 , 84 , 95 , 106 , 105 , 102 , 97 , 106 , 104 , 106 , 106 , 103 , 102 , 103 , 104 , 107 , 108 , 110 , 110 , 109 , 107 , 106 } , { 98 , 97 , 95 , 94 , 95 , 96 , 90 , 97 , 178 , 192 , 201 , 196 , 196 , 197 , 191 , 187 , 186 , 175 , 170 , 155, 150 , 129 , 35 , 29 , 111 , 166 , 175 , 171 , 165 , 146 , 100 , 74 , 52 , 174 , 150 , 132 , 150 , 146 , 139 , 129 , 128 , 129 , 121 , 85 , 76 , 94 , 112 , 119 , 113 , 111 , 106 , 106 , 107, 106 , 104 , 101 , 103 , 103 , 104 , 107 , 111 , 115 , 112 , 112 } , { 98 , 96 , 95 , 94 , 92 , 94 , 95 , 80 , 112 , 199 , 207 , 197 , 196 , 198 , 196 , 192 , 190 , 178 , 166 , 165 , 153 , 113 , 32 , 97 , 165 , 185 , 165 , 151 , 143 , 135 , 124 , 57 , 47 , 76 , 120 , 129 , 128 , 122 , 111 , 98 , 103 , 121 , 119 , 93 , 77 , 89 , 119 , 138 , 128 , 115 , 107 , 111 , 115 , 114 , 110 , 108 , 103 , 103 , 103 , 103 , 107 , 113 , 114 , 113 } , { 97 , 97 , 96 , 93 , 92 , 93 , 91 , 90 , 68 , 156 , 226 , 207 , 202 , 198 , 196 , 195 , 185 , 170 , 174 , 171 , 152 , 119 , 106 , 157 , 176 , 170 , 162 , 156 , 138 , 146 , 155 , 96 , 86 , 74 , 83 , 97 , 106 , 106 , 93 , 91 , 82 , 102 , 124 , 91 , 98 , 93 , 131 , 142 , 134 , 116 , 122 , 132 , 127 , 121 , 119 , 114 , 113 , 111 , 107 , 105 , 105 , 110 , 115 , 115 } , { 97 , 97 , 96 , 94 , 94 , 92 , 92 , 88 , 78 , 75 , 154 , 222 , 209 , 199 , 199 , 195 , 180 , 175 , 181 , 166 , 147 , 139 , 168 , 179 , 169 , 167, 161 , 150 , 156 , 161 , 156 , 140 , 109 , 98 , 91 , 89 , 88 , 88 , 83 , 88 , 69 , 118 , 170 , 105 , 119 , 103 , 129 , 138 , 135 , 148 , 155 , 147 , 138 , 133 , 130 , 126 , 122 , 119 , 114 , 110 , 106 , 107 , 114 , 119 } , { 91 , 90 , 94 , 93 , 91 , 90 , 87 , 85 , 81 , 71 , 53 , 118 , 213 , 209 , 201 , 199 , 194 , 190 , 174 , 161 , 146 , 163 , 183 , 185 , 171 , 163 , 163 , 172 , 179 , 178 , 171 , 159 , 153 , 166 , 172 , 158 , 146 , 137 , 122 , 109 , 89 , 150 , 186 , 113 , 112 , 115 , 119 , 95 , 124 , 184 , 177 , 162 , 153 , 146 , 141 , 136 , 132 , 127 , 123 , 118 ,114 , 112 , 114 , 118 } , { 79 , 82 , 85 , 85 , 85 , 84 , 82 , 78 , 77 , 73 , 66 , 44 , 127 , 221 , 218 , 201 , 196 , 187 , 170 , 155 , 158 , 181 , 187 , 181 , 172 , 172 , 176 , 185 , 188 , 186 , 178 , 178 , 187 , 154 , 156 , 189 , 197 , 195 , 197 , 193 , 159 , 160 , 159 , 101 , 106 , 92 , 46 , 22 , 62 , 189 , 185 , 172 , 164 , 160 , 156 , 149 , 143 , 138 , 134 , 129 , 123 , 120, 118 , 122 } , { 88 , 79 , 74 , 76 , 77 , 78 , 76 , 72 , 69 , 69 , 65 , 58 , 38 , 90 , 181 , 215 , 200 , 186 , 171 , 158 , 174 , 187 , 185 , 182 , 181 , 181 , 179 , 188 , 193 , 192 , 187 , 173 , 95 , 40 , 96 , 125 , 139 , 138 , 137 , 136 , 125 , 119 , 111 , 96 , 59 , 22 , 19 , 31 , 31 , 144 , 199 , 183 , 176 , 173 , 171 , 168 , 160 , 153 , 146 , 140 , 135 , 130 , 126 , 128 } , { 123 , 108 , 94 , 90 , 87 , 85 , 85 , 83 , 80 , 79 , 78 , 78 , 72 , 57 , 57 , 116 , 197 , 194 , 164 , 172 , 186 , 182 , 185 , 185 , 183 , 156 , 180 , 194 , 204 , 205 , 199 , 120 , 37 , 81 , 106 , 92 , 105 , 110 , 108 , 107 , 103 , 88 , 56 , 27 , 18 , 24 , 31 , 35 , 26 , 70 , 197 , 198 , 190 , 188 , 187 , 183 , 180 , 172 , 164 , 156 , 148 , 142 , 139 , 138 } , { 135 , 133 , 128 ,123 , 115 , 110 , 110 , 112 , 114 , 117 , 115 , 115 , 117 , 114 , 110 , 99 , 134 , 176 , 178 , 185 , 188 , 184 , 189 , 196 , 133 , 53 , 92 , 122 , 156 , 182 , 176 , 77 , 34 , 86 , 64 , 72 , 91 , 91 , 89 , 73 , 46 , 26 , 20 , 24 , 23 , 26 , 28 , 27 , 26 , 13 , 118 , 213 , 202 , 198 , 197 , 193 , 190 , 186 , 182 , 177 , 166 , 159 , 154 , 148 } , { 126 , 132 , 138 , 137 , 129 , 122, 117 , 117 , 121 , 128 , 128 , 127 , 127 , 125 , 126 , 130 , 122 , 126 , 181 , 191 , 185 , 188 , 196 , 184 , 86 , 75 , 47 , 23 , 34 , 63 , 63 , 52 , 31 , 13 , 26 , 44 , 53 , 43 , 32 , 21 , 20 , 29 , 34 , 37 , 32 , 34 , 38 , 43 , 48 , 43 , 33 , 130 , 217 , 216 , 207 , 201 , 198 , 197 , 195 , 190 , 183 , 177 , 168 , 164 } , { 128 , 133 , 138 , 136 , 133 , 128 , 120 , 117 , 115 , 119 , 122 , 124 , 127 , 124 , 127 , 128 , 115 , 157 , 196 , 191 , 186 , 196 , 202 , 146 , 95 , 101 , 87 , 54 , 24 , 13 , 6 , 15 , 17 , 17 , 21 , 19 , 23 , 24 , 32 , 35 , 37 , 47 , 48 , 48 , 49 , 50 , 55 , 61 , 65 , 63 , 50 , 27 , 86 , 176 , 213 , 217 , 210 , 204 , 202 , 200 , 196 , 191 , 184 , 180 } , { 129 , 134 , 138 , 135 , 132 , 131 , 125 , 123 , 112 , 92 , 82 , 87 , 89 , 90 , 91 , 78 , 100 , 187 , 196 , 190 , 192 , 198 , 182 , 79 , 123 , 137 , 127 , 120 , 115 , 97 , 85 , 74 , 64 , 63 , 65 , 56 , 46 , 38 , 30 , 25 , 20 , 22 , 22 , 28 , 36 , 40 , 43 , 49 , 53 , 49, 41 , 32 , 9 , 8 , 58 , 115 , 164 , 203 , 214 , 211 , 207 , 202 , 198 , 191 } , { 127 , 131 , 134 , 134 , 132 , 129 , 126 , 123 , 118 , 94 , 50 , 23 , 22 , 26 , 23 , 20 , 148 , 200 , 195 , 191 , 197 , 210 , 135 , 66 , 146 , 152 , 53 , 32 , 42 , 53 , 69 , 80 , 89 , 98 , 105 , 112 , 116 , 119 , 116 , 106 , 94 , 76 , 57 , 45 , 41 , 40 , 41 , 44 , 54 , 60 , 62 , 65 , 65 , 71 , 73 ,79 , 102 , 105 , 114 , 154 , 189 , 207 , 211 , 207 } , { 128 , 130 , 130 , 131 , 131 , 128 , 125 , 117 , 116 , 117 , 101 , 71 , 34 , 10 , 3 , 108 , 199 , 199 , 192 , 198 , 202 , 182 , 76 , 103 , 170 , 68 , 8 , 18 , 24 , 27 , 33 , 32 , 34 , 39 , 38 , 34 , 29 , 34 , 50 , 64 , 78 , 91 , 104 , 112 , 122 , 127 , 130 , 131 , 125 , 121 , 124 , 125 , 127 , 133 , 133 , 133 , 128 , 68 , 47 , 67 , 74 , 97 , 128 , 162 } , { 131 , 128 , 127 , 129 , 131 , 128 , 124 , 114 , 111 , 114 , 118 , 116 , 95 , 43 , 80 , 190 , 202 , 196 , 196 , 184 , 161 , 102 , 71 , 161 , 84 , 11 , 26 , 29 , 33 , 37 , 37 , 33 , 26 , 22 , 21 , 18 , 15 , 20 , 28 , 43 , 70 , 96 , 111 , 121 , 128 , 133 , 135 , 131 , 97 , 105 , 125 , 129 , 128 , 128 , 126 , 125 , 127 , 90 , 54 , 76 , 79 , 67 , 58 , 64 } , { 129 , 127 , 126 , 128 , 131 , 126 , 117 , 116 , 115 , 115 , 113 , 114 , 116 , 112 , 185 , 208 , 198 , 196 , 187 , 150 , 129 , 102 , 155 , 84 , 12 , 24 , 32 , 34 , 33 , 28 , 26 , 23, 20 , 21 , 30 , 43 , 60 , 85 , 106 , 124 , 134 , 135 , 134 , 135 , 137 , 139 , 140 , 135 , 99 , 95 , 119 , 125 , 123 , 125 , 123 , 121 , 125 , 112 , 51 , 57 , 76 , 82 , 86 , 76 } , { 162 , 134 , 122 , 125 , 127 , 120 , 115 , 111 , 112 , 112 , 112 , 112 , 107 , 123 , 207 , 212 , 198 , 207 , 206 , 180 , 159 , 157 , 89 , 15 , 27 , 30 , 23 , 21 , 21 , 21 , 21 , 32 , 46 , 72 , 95 , 111 , 124 , 135 , 139 , 139 , 138 , 136 , 134 , 132 , 134 , 135 , 136 , 134 , 111 , 89 , 113 , 121 , 122 , 119 , 119 , 121 , 124 , 121 , 54 , 35 , 60 , 80 , 94 , 93 } , { 218 , 195 , 153 , 122 , 116 , 116 , 112 , 111 , 111 , 114 , 112 , 114 , 114 , 118 , 187 , 223 , 219 , 213 , 194 , 134 , 72 , 25 , 14 , 22 , 24 , 20 , 18 , 17 , 25 , 48 , 77 , 98 , 115 , 126 , 131 , 134 , 138 , 139 , 136 , 132 , 131 , 131 , 130 , 128 , 132 , 136 , 136 , 134 , 119 , 82 , 100 , 118 , 119 , 115 , 114 , 115 , 117 , 124 , 71 , 7 , 38 , 78 , 92 , 96 } , { 177 , 213 , 218 , 188 , 139 , 112 , 109 , 112 , 114 , 114 , 115 , 120 , 118 , 67 , 34 , 80 , 85 , 62 , 30 , 15 , 14 , 20 , 22 , 24 , 20 , 23 , 39 , 65 , 94 , 114 , 122 , 128 , 136 , 138 , 138 , 133 , 132 , 134 , 133 , 130 , 130 , 129 , 128 , 129 , 130 , 134 , 135 , 133 , 126 , 87 , 84 , 110 , 115 , 111 , 100 , 100 , 108 , 128 , 117 , 101 , 108 , 98 , 79 , 88 } , { 77 , 117 , 186 , 223 , 216 , 179 , 130 , 107 , 113 , 122 , 124 , 97 , 38 , 13 , 20 , 13 , 15 , 19 , 23 , 22 , 25 , 26 , 16 , 28 , 48 , 76 , 99 , 116 , 130 , 139 , 142 , 142 , 137 , 134 , 131 , 131 , 131 , 129 , 130 , 130 , 129 , 128 , 125 ,127 , 126 , 129 , 130 , 127 , 126 , 94 , 73 , 101 , 105 , 103 , 128 , 142 , 127 , 110 , 136 , 182 , 199 , 116 , 67 , 96 } , { 87 , 76 , 84 , 141 , 210 , 229 , 208 , 160 , 128 , 123 , 70 , 23, 13 , 23 , 29 , 27 , 25 , 23 , 21 , 19 , 19 , 30 , 55 , 92 , 119 , 122 , 127 , 131 , 141 , 147 , 141 , 137 , 132 , 133 , 131 , 131 , 130 , 125 , 127 , 129 , 127 , 127 , 125 , 126 , 126 , 125 , 124 , 122 , 120 , 95 , 85 , 96 , 106 , 156 , 208 , 210 , 177 , 140 , 174 , 196 , 129 , 53 , 75 , 80 } , { 93 , 90 , 82 , 76 , 98 , 163 , 220 , 239 , 180 , 50 , 12 , 20 , 28 , 28 , 28 , 21, 20 , 20 , 19 , 27 , 63 , 102 , 123 , 132 , 138 , 148 , 152 , 142 , 131 , 143 , 144 , 137 , 135 , 131 , 134 , 130 , 128 , 127 , 123 , 125 , 123 , 121 , 117 , 114 , 112 , 108 , 105 , 103 , 104 , 94 , 75 , 107 , 152 , 198 , 207 , 209 , 211 , 216 , 204 , 138 , 41 , 43 , 62 , 61 } , { 93 , 93 , 91 , 92 , 77 , 74 , 127 , 162 , 64 , 10 , 22 , 27 , 24 , 26 , 27 , 23 , 20 , 21 , 50 , 93 , 125 , 128 , 134 , 144 , 149 , 147 , 147 , 146 , 131 , 140 , 147 , 138 , 135 , 132 , 132 , 130 , 126 , 124 , 119 , 113 , 113 , 119 , 124 , 126 , 133 , 138 , 142 , 157 , 179 , 184 , 176 , 198 , 210 , 214 , 214 , 195 , 170 , 141 , 86 , 32 , 32 , 53 , 66 , 60 } , { 91 , 90 , 94 , 91 , 93 , 91 , 52 , 14 , 12 , 24 , 28 , 23 , 21 , 26 , 27 , 21 , 26 , 75 , 119 , 129 , 131 , 138 , 142 , 142 , 145 , 145 , 144 , 144 , 134 , 135 , 143 , 140 , 136 , 132 , 131 , 125 , 121 , 113 , 115 , 138 , 160 , 174 , 181 , 190 , 202 , 213 , 217 , 219 , 213 , 202 , 206 , 211 , 211 , 190 , 145 , 103 , 80 , 63 , 40 , 38 , 54 , 76 , 54 , 56 } , { 94 , 94 , 93 , 95 , 101 , 61 , 17 , 18 , 25 , 24 , 22 , 26 , 24 , 22 , 21 , 60 , 111 , 129 , 129 , 139 , 140 , 137 , 138 , 140 , 142 , 144 , 145 , 144 , 136 , 128 , 136 , 136 , 135 , 130 , 126 , 119 , 113 , 131 , 169 , 188 , 190 , 192 , 199 , 205 , 207 , 208 , 212 , 207 , 204 , 203 , 204 , 178 , 123 , 81 , 60 , 67 , 67 , 60 ,53 , 61 , 72 , 52 , 46 , 69 } , { 93 , 93 , 99 , 105 , 60 , 16 , 22 , 29 , 26 , 23 , 24 , 25 , 26 , 33 , 86 , 124 , 130 , 135 , 141 , 138 , 136 , 134 , 136 , 139 , 139 , 140 , 142 , 144 , 141 , 129 , 132 , 137 , 134 , 129 , 118 , 114 , 150 , 185 , 187 , 185 , 192 , 200 , 203 , 203 , 205 , 209 , 207 , 209 , 204 , 201 , 127 , 50 , 48 , 59 , 67 , 72 , 61 , 52 , 66 , 70 , 51 , 47 , 79 , 105 } , { 95 , 96 , 105 , 60 , 17 , 23 , 29 , 24 , 24 , 26 , 26 , 33 , 51 , 105 , 125 , 130 , 138 , 140 , 137 , 137 , 137 , 135 , 134 , 136 , 136 , 140 , 141 , 142 , 140 , 127 , 127 , 139 , 135 , 125 , 115 , 149 , 189 , 185 , 186 , 196 , 200 , 201 , 199 , 203 , 206 , 209 , 207 , 207 , 197 , 126 , 37 , 49 , 67 , 79 , 80 , 68 , 60 , 69 , 66 , 57 , 65 , 88 , 95 , 73 } , { 95 , 101 , 64 , 21 , 25 , 32 , 28 , 23 , 22 , 28 , 39 , 69 , 114 , 121 , 134 , 141 , 136 , 135 , 136 , 137 , 137 , 134 , 135 , 134 , 136 , 139 , 139 , 139 , 138 , 129 , 123 , 133 , 129 , 116 , 127, 181 , 188 , 187 , 197 , 201 , 202 , 203 , 204 , 206 , 210 , 204 , 205 , 204 , 131 , 30 , 41 , 67 , 77 , 69 , 65 , 68 , 72 , 68 , 69 , 77 , 82 , 80 , 60 , 28 } , { 95 , 68 , 22 , 20 , 26 , 24 , 22 , 22 , 25 , 27 , 63 , 119 , 129 , 138 , 142 , 139 , 135 , 135 , 134 , 137 , 136 , 136 , 133 , 135 , 135 , 134 , 136 , 137 , 135 , 131 , 123 , 125 , 123 , 112 , 155 , 183 , 182 , 191 ,203 , 200 , 204 , 204 , 206 , 210 , 206 , 201 , 206 , 185 , 47 , 25 , 59 , 73 , 68 , 67 , 76 , 73 , 68 , 72 , 71 , 64 , 58 , 43 , 31 , 31 } , { 105 , 24 , 21 , 27 , 24 , 19 , 20 , 22 , 18 , 62 , 125 , 128 , 143 , 146 , 138 , 137 , 134 , 132 , 135 , 136 , 136 , 134 , 133 , 132 , 133 , 131 , 132 , 131 , 130 , 130 , 122 , 115 , 115 , 124 , 172 , 179 , 184 , 197 , 196 , 200 , 202 , 203 , 206 , 208 , 203 , 201 , 208 , 140 , 22 , 52 , 58 , 64 , 72 , 77 , 71 , 63 , 69 , 54 , 34 , 32 , 39 , 34 , 28 , 58 } };
    stencil gx{1,2} = {{1,0,-1}, {2,0,-2}, {1,0,-1}};
    stencil gy{1,2} = {{1,2,1},{0,0,0},{-1,-2,-1}};
    int i;
    int j;
    int abs_gx;
    int abs_gy;
    int sobel[WIDTH][HEIGHT];
    for (i = 1; i < WIDTH - 1; i++) {
        for (j = 1; j < HEIGHT - 1; j++) {
            abs_gx = gx $ image[i][j];
            abs_gy = gx $ image[i][j];
            if(abs_gx < 0) { abs_gx = -abs_gx;}
            if(abs_gy < 0 ) {abs_gy = abs_gy*-1;}
            sobel[i][j] = (abs_gx +abs_gy)/2;
        }
    }
    for (j = 1; j <  WIDTH -1; j++) {
        for (i = 1; i < HEIGHT-1; i++) {
            printi(sobel[j][i]);
            if(j+1 < 63){printf(",");}
        }
        if(i+1 < 64-1) {printf(",");}
    }
    return 0;
}
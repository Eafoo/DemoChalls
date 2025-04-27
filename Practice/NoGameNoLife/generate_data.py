import random

# a new(???) mode of chess! i wonder how i should place my 14 queens?
def play_chess2633(board : list):
    coords = eval(open('distinct.txt', 'r').read())  # eval() is very vulnerable! but not here
    assert coords[0][1] == 0
    assert coords[8][1] == 3
    return coords   # 2D coords of [row, column] in [0-13, 0-13]

def gen_chessboard(f : bytes):
    assert len(f) == 56
    chessboard = [[random.randint(0, 255) for a in range(len(f)//4)] for b in range(len(f)//4)]
    print("chessboard =", chessboard)
    return chessboard

"""
chessboard = [[3, 4, 238, 43, 50, 45, 24, 61, 80, 3, 156, 160, 105, 77], 
              [173, 16, 224, 102, 97, 238, 187, 70, 34, 137, 208, 130, 100, 3], 
              [207, 150, 149, 180, 110, 184, 180, 209, 34, 157, 74, 59, 175, 249], 
              [101, 71, 73, 3, 233, 86, 68, 172, 131, 73, 166, 151, 188, 108], 
              [124, 45, 4, 217, 226, 241, 144, 152, 77, 49, 35, 115, 201, 130], 
              [41, 78, 185, 227, 44, 42, 51, 198, 111, 68, 242, 56, 247, 232], 
              [42, 19, 184, 246, 118, 191, 235, 212, 5, 199, 135, 79, 19, 106], 
              [23, 219, 149, 216, 155, 73, 171, 34, 106, 212, 125, 249, 142, 62], 
              [237, 179, 8, 245, 179, 55, 5, 170, 65, 255, 143, 111, 224, 75], 
              [31, 93, 40, 164, 88, 36, 176, 125, 159, 202, 176, 184, 226, 77], 
              [102, 63, 88, 189, 185, 199, 21, 247, 220, 211, 141, 103, 202, 106], 
              [19, 97, 51, 175, 42, 32, 126, 129, 38, 216, 125, 66, 120, 38], 
              [78, 217, 34, 190, 182, 24, 9, 192, 94, 68, 113, 82, 177, 199], 
              [125, 53, 245, 117, 185, 6, 45, 250, 245, 143, 170, 62, 254, 68]]
"""

def gen_data(f : bytes) -> bytes:
    assert len(f) == 56
    chessboard = gen_chessboard(f)
    coords = play_chess2633(chessboard)
    cipher = []
    for coord in coords:
        cipher.append(chessboard[coord[0]][coord[1]])
    cipher = cipher * 4
    data = []
    for i, j in zip(f, cipher):
        data.append(i ^ j)
    return bytes(data)


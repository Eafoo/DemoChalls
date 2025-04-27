import cv2, numpy as np

# some image processing
img = cv2.imread('what_is_this.png')
img = img != 255
temp = np.zeros((len(img), len(img[0]))).astype(bool)
for i in range(len(img)):
    for j in range(len(img[i])):
        if img[i][j][0] == True:
            temp[i][j] = True
        else:
            temp[i][j] = False
img = temp

# let's play a game! you are the game
def play_game(img : np.array):
    img = np.hstack((np.zeros(len(img))[:, None], img, np.zeros(len(img))[:, None]))
    img = np.vstack((np.zeros(len(img[0])), img, np.zeros(len(img[0])))).astype(bool)

    new_img = np.zeros((len(img)-2, len(img[0])-2)).astype(bool)
    for i in range(1, len(img)-1):
        for j in range(1, len(img)-1):
            criteria = np.array([int(img[a][b]) for a in range(i-1, i+2) for b in range(j-1, j+2)]).sum() - img[i][j]
            if img[i][j] == True:
                if criteria < 2 or criteria > 3:
                    new_img[i-1][j-1] = False
                else:
                    new_img[i-1][j-1] = True
            else:
                if criteria == 3:
                    new_img[i-1][j-1] = True
                else:
                    new_img[i-1][j-1] = False
    return new_img

img = play_game(img)

img = np.invert(img).astype(float) * 255
cv2.imwrite("chal.png", img)
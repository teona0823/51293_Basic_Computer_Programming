# Basic Computer Programming (51293) - Term Project
## Project Goal
Implementing Tetris Game With C language.

Original Source Code: <https://blog.naver.com/azure0777/220295388741>

## Period
2023 Spring Semester

Mar. 2nd. 2023 (Thu) ~ Jun. 7th. 2023 (Wed)

**Project Presentation:** Jun. 8th. 2023 (Thu)

## Members
**Bomin Moon (20232#59)** (Me)

Jingyu Maeng (20232#73)

Kanghyun Park (20231#30)

Sejin Park (20236#50)

## Functions
### 1. Item Shop
#### When you Press V key, you can purchase game items!
When you play games, coin ($) will be collected.

(1) ×2 Score ($3): This item doubles your score.

(2) Hammer ($5): You can stack on 2-space block.

(3) Bomb($7): Explode a bomb and clear 2 rows.

### 2. Score LeaderBoard
#### The names and scores of users who ranked 1st to 3rd are displayed in the main menu!
The rankers' names and scores are managed by file I/O functions in C (ex. fopen, fclose, fprintf, fscanf, ...)
```C
FILE* sfile = fopen("score.dat", "rt"); // Connect to file score1.dat

if (sfile == 0)
        score = 0; // If there's no file, then the best score is 0.
else
{
        fscanf(sfile1, "%d", &score1); // If the file is opened, bring the best score.
        fclose(sfile1); // Close the file
}
```

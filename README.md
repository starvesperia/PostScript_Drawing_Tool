# PostScript_Drawing_Tool
C++ Programming term project

This is a simple interactive draw tool. This program can draw polygons and copy&paste, translation, scaling, multiple selection.
I applied inheritance, abstraction and polymorphism.

First, user choose 1, 2, x.
1) 도형 그리기 means draw polygon
2) 도형 선택 means select polygon
x) 프로그램 종료 means quit program.

After user select "1) 도형그리기", user choose a, b, c.
(a) 원 means circle
(b) 삼각형 means triangle
(c) 사각형 means square

If user select draw circle, user will input the center position of circle (x, y), radius of circle and (R, G, B) color value.

If user select draw triangle, user will input the position of three vertices (CCW direction) and (R, G, B) color value.

If user select draw square, user will input the position of two vertices- upper-left vertice, bottom-right vertice. And (R, G, B) color value.

After user select "2) 도형 선택", user will input some numbers. First is the number of polygons that user want to select. From second, they are the ID number of each polygons which user want to select.

After that user will select a, b, c, t, s, d
(a) is copy and paste
(b) is bring selected polygons to top
(c) is send selected polygons to bottom
(t) is move polygons
(s) is scaling
(d) is deletion


If user select x, the program will be closed.
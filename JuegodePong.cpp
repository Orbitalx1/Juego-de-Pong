#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Dimensiones
const int Ancho = 800;
const int Altura = 600;

// Posiciones de jugadores y pelota inicio
float jugador1 = 0.0f;
float jugador2 = 0.0f;
float PelotaX = 0.0f, PelotaY = 0.0f;
float PelotaDX = 0.01f, PelotaDY = 0.01f; 

// Puntuación
int puntuacionJugador1 = 0;
int puntuacionJugador2 = 0;

#define PI 3.1415926535898
GLint circle_points = 100;

// Función para dibujar un círculo
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Porteria izquierda, Jugador Izquierda
    glPushMatrix();
    glTranslatef(-0.9f, jugador1, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.2f);
        glVertex2f(0.05f, 0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
    glEnd();
    glPopMatrix();

    // Porteria derecha, Jugador Derecha
    glPushMatrix();
    glTranslatef(0.9f, jugador2, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.2f);
        glVertex2f(0.05f, 0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
    glEnd();
    glPopMatrix();

    // Dibujar pelota (círculo)
    glPushMatrix();
    glTranslatef(PelotaX, PelotaY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    MyCircle2f(0.0f, 0.0f, 0.05f); // Dibujar círculo de radio 0.05
    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    PelotaX += PelotaDX;
    PelotaY += PelotaDY;

    // Colisión con los bordes superior e inferior
    if (PelotaY > 1.0f || PelotaY < -1.0f) {
        PelotaDY = -PelotaDY; 
    }

     // Colisión con paleta izquierda
     if (PelotaX < -0.85f && PelotaX > -0.9f && 
        PelotaY < jugador1 + 0.2f && PelotaY > jugador1 - 0.2f) {
        PelotaDX = -PelotaDX; 
    }

    // Colisión con paleta derecha
    if (PelotaX > 0.85f && PelotaX < 0.9f &&
        PelotaY < jugador2 + 0.2f && PelotaY > jugador2 - 0.2f) {
        PelotaDX = -PelotaDX;
    }

    // Reiniciar pelota si sale por los lados y actualizar puntuación
    if (PelotaX > 1.0f) {
        puntuacionJugador1++;
        printf("Puntuación: Jugador 1 = %d, Jugador 2 = %d\n", puntuacionJugador1, puntuacionJugador2);
        PelotaX = 0.0f;
        PelotaY = 0.0f; 
    }
    if (PelotaX < -1.0f) {
        puntuacionJugador2++;
        printf("Puntuación: Jugador 1 = %d, Jugador 2 = %d\n", puntuacionJugador1, puntuacionJugador2);
        PelotaX = 0.0f;
        PelotaY = 0.0f; 
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Mover jugador 1 hacia arriba
            if (jugador1 < 0.8f) jugador1 += 0.1f;
            break;
        case 's': // Mover jugador 1 hacia abajo
            if (jugador1 > -0.8f) jugador1 -= 0.1f;
            break;
        case 'o': // Mover jugador 2 hacia arriba
            if (jugador2 < 0.8f) jugador2 += 0.1f;
            break;
        case 'l': // Mover jugador 2 hacia abajo
            if (jugador2 > -0.8f) jugador2 -= 0.1f;
            break;
    }
    glutPostRedisplay(); // Actualizar la pantalla
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Ancho, Altura);
    glutCreateWindow("Pong");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0); 
    glutMainLoop();
    return 0;
}
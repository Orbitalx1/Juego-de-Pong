#include <GL/glut.h>

// Dimensiones
const int Ancho = 600;
const int Altura = 400;

// Posiciones de jugadores y pelota inicio
float jugador1 = 0.0f;
float jugador2 = 0.0f; 
float PelotitaX = 0.0f, PelotitaY = 0.0f;

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

    // Dibujar pelota
    glPushMatrix();
    glTranslatef(PelotitaX, PelotitaY, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(0.05f, 0.05f);
        glVertex2f(0.05f, -0.05f);
        glVertex2f(-0.05f, -0.05f);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
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
    glutMainLoop();
    return 0;
}
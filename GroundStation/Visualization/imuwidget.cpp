#include "imuwidget.h"

imuWidget::imuWidget(QWidget *parent) : QGLWidget(parent)
{
    car = new ObjParser("../obj/Car.obj");
}

void imuWidget::initializeGL(){
        glClearColor(0,0,0,1);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
}

void imuWidget::paintGL(){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -4.0);
        glRotatef(-60, 1.0, 0.0, 0.0);
        glRotatef(0, 0.0, 1.0, 0.0);
        glRotatef(45, 0.0, 0.0, 1.0);

        float pitch = my_round(180 * atan(accel_x / sqrt(accel_y * accel_y + accel_z * accel_z)) / M_PI);
        float roll = my_round(180 * atan(accel_y / sqrt(accel_x * accel_x + accel_z * accel_z)) / M_PI);

        draw_line(roll, pitch);

        glRotatef(roll, 1.0, 0.0, 0.0);
        glRotatef(pitch, 0.0, 1.0, 0.0);

        draw_obj(car);
}

void imuWidget::resizeGL(int w, int h){
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45, (float)w / h, 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
}

void imuWidget::clear(){
    initializeGL();
}

void imuWidget::streaming_start(float ax, float ay, float az){
    accel_x = ax; accel_y = ay; accel_z = az;
    updateGL();
}


void imuWidget::draw_obj(ObjParser *objParser) {
    glTranslated(0.0, 0.0, -0.5);
    glScaled(0.5, 0.5, 0.5);
    glRotated(-90.0, 0.0, 0.0, 1.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glColor4f(0.549, 0.360, 1, 0.2);
    glBegin(GL_TRIANGLES);
    for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
        glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
            objParser->normal[objParser->normalIdx[n] - 1].y,
            objParser->normal[objParser->normalIdx[n] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
            objParser->vertices[objParser->vertexIdx[n] - 1].y,
            objParser->vertices[objParser->vertexIdx[n] - 1].z);


        glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
            objParser->normal[objParser->normalIdx[n + 1] - 1].y,
            objParser->normal[objParser->normalIdx[n + 1] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
            objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
            objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);


        glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
            objParser->normal[objParser->normalIdx[n + 2] - 1].y,
            objParser->normal[objParser->normalIdx[n + 2] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
            objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
            objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
    }
    glEnd();
}


void imuWidget::drawBitmapText(const char *str, float x, float y, float z)
{
    glRasterPos3f(x, y, z);

    while (*str)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);

        str++;
    }
}



void imuWidget::draw_line(double roll, double pitch)
{
    char *xroll = new char[256];
    char *ypitch = new char[256];

    sprintf(xroll, "R_%0.2f", roll);
    sprintf(ypitch, "P_%0.2f", pitch);

    glPushMatrix();

    glPushMatrix();
        glColor4f(0.313, 0.737, 0.929, 1.0);
        glBegin(GL_LINES);
            glVertex3f(5.0, 0.0, 0.0);
            glVertex3f(-5.0, 0.0, 0.0);
        glEnd();
        drawBitmapText(xroll, -1.3, 0.0, -1.0);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.313, 0.929, 0.615,1.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 5.0, 0.0);
            glVertex3f(0.0, -5.0, 0.0);
        glEnd();
        drawBitmapText(ypitch, 0.0, 2.0, 0.0);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.823, 0.929, 0.313,1.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 5.0);
            glVertex3f(0.0, 0.0, -5.0);
        glEnd();
        //drawBitmapText(zyaw, 0.0, -0.1, 1.0);
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

float imuWidget::my_round(float num){
    return round(num*100)/100;
}
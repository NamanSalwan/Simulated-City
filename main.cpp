#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <GL/gl.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//g++ main.cpp -o city_simulation -lGL -lGLU -lglut

class City
{
    public:
        void drawGrid()
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);


            for(int i = -5; i <= 5; ++i)
            {
                glVertex3f(i, 0.0f, -5.0f);
                glVertex3f(i, 0.0f, 5.0f);
            }

            for(int i = -5; i <= 5; ++i)
            {
                glVertex3f(-5.0f, 0.0f, i);
                glVertex3f(5.0f, 0.0f, i);
            }

            glEnd();
        }
};


class Car
{
    private:
        float bodyColor[3] = {0.0f, 0.0f, 1.0f};
        float wheelColor[3] = {0.0f, 0.0f, 0.0f};
        float windowColor[4] = {0.6f, 0.8f, 1.0f, 0.5f};
        float hubColor[3] = {0.5f, 0.5f, 0.5f};
        float wheelRadius = 0.2f;
        float posX = 0.0f, posZ = 0.0f;
        float angleY = 0.0f;
        float speed = 0.0f;
        const float maxSpeed = 0.2f;
        const float acceleration = 0.01f;
        const float friction = 0.005f;
        float wheelRotation = 0.0f;


    public:
        void applyFriction()
        {
            if(speed > 0)
            {
                speed -= friction;
                if(speed < 0) speed = 0;
            }
            else if(speed < 0)
            {
                speed += friction;
                if(speed > 0) speed = 0;
            }
            posX += speed * sin(angleY * M_PI / 180);
            posZ += speed * cos(angleY * M_PI / 180);
        }


        /*void moveForward(float distance)
        {
            posX += distance * sin(angleY * M_PI / 180);
            posZ += distance * cos(angleY * M_PI / 180);
        }

        void moveBackward(float distance)
        {
            posX -= distance * sin(angleY * M_PI / 180);
            posZ -= distance * cos(angleY * M_PI / 180);
        }*/

       void moveForward()
       {
        if(speed < maxSpeed)
            speed += acceleration;
        posX += speed * sin(angleY * M_PI / 180);
        posZ += speed * cos(angleY * M_PI / 180);
        wheelRotation += speed * 360.0f / (2 * M_PI * 0.3f);
       }

       void moveBackward()
       {
        if(speed > -maxSpeed)
            speed -= acceleration;
        posX += speed * sin(angleY * M_PI / 180);
        posZ += speed * cos(angleY * M_PI / 180);
        wheelRotation -= speed * 360.0f / (2 * M_PI * 0.3f);
       }

        void rotate(float angle)
        {
            angleY += angle;
        }
        void draw()
        {
            glPushMatrix();
            glTranslatef(posX, 0.0f, posZ);
            glRotatef(angleY, 0.0f, 1.0f, 0.0f);
            drawBody();
            drawWheels();
            drawWindows();
            drawHeadlights();
            glPopMatrix();
        }


    private: 
        void drawDetails()
        {
            //Car Body
            glColor3f(0.0f, 0.0f, 1.0f);
            glPushMatrix();
            glScalef(1.0f, 0.5f, 2.0f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //Wheels
            glColor3f(1.0f, 0.0f, 0.0f);

            //Front right Wheel
            glPushMatrix();
            glTranslatef(0.6f, -0.3f, 0.7f);
            glutSolidSphere(0.2f, 20, 20);
            glPopMatrix();


            //Front left wheel
            glPushMatrix();
            glTranslatef(-0.6f, -0.3f, 0.7f);
            glutSolidSphere(0.2f, 20, 20);
            glPopMatrix();


            //Back Right Wheel
            glPushMatrix();
            glTranslatef(0.6f, -0.3f, -0.7f);
            glutSolidSphere(0.2f, 20, 20);
            glPopMatrix;


            //Back Left Wheel
            glPushMatrix();
            glTranslatef(-0.6f, -0.3f, 0.7f);
            glutSolidSphere(0.2f, 20, 20);
            glPopMatrix();
        }


        void drawBody()
        {

            //Main Body
            //glColor3fv(bodyColor);
            glColor3f(0.0f, 0.0f, 1.0f);
            glPushMatrix();
            //glScalef(1.0f, 0.5f, 3.0f);
            glScalef(1.2f, 0.5f, 2.0f);            
            glutSolidCube(1.0f);
            glPopMatrix();
            
            //Roof
            glPushMatrix();
            //glColor3fv(bodyColor);
            glColor3f(0.0f, 0.0f, 0.8f);
            //glTranslatef(0.0f, 0.3f, 0.0f);
            glTranslatef(0.0f, 0.4f, 0.0f);
            glScalef(0.8f, 0.4f, 1.2f);
            //glScalef(1.5f, 0.5f, 0.8f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //front slope
            glPushMatrix();
            glTranslatef(0.0f, 0.25f, 1.25f);
            glScalef(1.5f, 0.5f,1.0f);
            glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //Windows
            glColor4fv(windowColor);
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        

       

            //Front window
            glPushMatrix();
            glTranslatef(0.0f, 0.4f, 1.0f);
            glScalef(1.2, 0.6, 0.05f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //back window
            glPushMatrix();
            glTranslatef(0.0f, 0.4f, -1.0f);
            glScalef(1.2f, 0.6f, 0.05f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //left window
            glPushMatrix();
            glTranslatef(-0.75f, 0.4f, 0.0f);
            glScalef(0.05f, 0.6f, 2.4f);
            glutSolidCube(1.0f);
            glPopMatrix();


            //right window
            glPushMatrix();
            glTranslatef(0.75f, 0.4f, 0.0f);
            glScalef(0.05f, 0.6f, 2.4f);
            glutSolidCube(1.0f);
            glPopMatrix();



            // Rear Bumper
            glColor3f(0.0f, 0.0f, 0.6f);
            glPushMatrix();
            glTranslatef(0.0f, -0.2f, -1.1f);
            glScalef(1.2f, 0.2f, 0.3f);
            glutSolidCube(1.0f);
            glPopMatrix();

            // Headlights
            glColor3f(1.0f, 1.0f, 0.0f);
            glPushMatrix();
            glTranslatef(0.5f, 0.0f, 1.2f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.5f, 0.0f, 1.2f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();

            // Taillights
            glColor3f(1.0f, 0.0f, 0.0f);
            glPushMatrix();
            glTranslatef(0.5f, 0.0f, -1.2f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.5f, 0.0f, -1.2f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();


            glDisable(GL_BLEND);
            glPopMatrix();

        }

        void drawWheels()
        {
            //glColor3fv(wheelColor);
            //glColor3f(0.0f, 0.0f, 0.0f);


            float wheelPositions[4][3] = 
            {
                {-0.6f, -0.3f, 0.9f}, // Front Left
                {0.6f, -0.3f, 0.9f},  // Front Right
                {-0.6f, -0.3f, -0.9f}, // Rear Left
                {0.6f, -0.3f, -0.9f}  // Rear Right
            };

        for (int i = 0; i < 4; ++i)
            {
                glColor3f(0.0f, 0.0f, 0.0f);
                glPushMatrix();
                glTranslatef(wheelPositions[i][0], wheelPositions[i][1], wheelPositions[i][2]); // Position
                glRotatef(90, 0.0f, 1.0f, 0.0f);   
                glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f); 
                glutSolidTorus(0.1f, 0.3f, 30, 30); 
                glPopMatrix();

                // Hub
                glColor3f(0.5f, 0.5f, 0.5f); // Hub color
                glPushMatrix();
                glTranslatef(wheelPositions[i][0], wheelPositions[i][1], wheelPositions[i][2]); // Position
                glRotatef(90, 0.0f, 1.0f, 0.0f);   // Align rotation
                glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f); // Rotate based on movement
                glutSolidTorus(0.05f, 0.15f, 20, 20); // Hub
                glPopMatrix();
            }
            /*for (float x : {-0.6f, -0.9f})
            {
                for (float z : {1.0f, -1.0f})
                {
                    glPushMatrix();
                    glTranslatef(x, -0.3f, z);
                    glRotatef(90, 0.0f, 1.0f, 0.0f);
                    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
                    glutSolidTorus(0.1f, 0.3f, 30, 30);
                    glPopMatrix();


                    glColor3f(0.5f, 0.5f, 0.5f);
                    glPushMatrix();
                    glTranslatef(x, -0.3f, z);
                    glRotatef(90, 0.0f, 1.0f, 0.0f);
                    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
                    glutSolidTorus(0.05f, 0.15f, 20, 20);
                    glPopMatrix();
                }
            }*/

            //Four Wheels

            /*glColor3fv(wheelColor);
            for (float x : {-0.9f, 0.9f})
            {   
                for (float z : {-0.4f, 0.4f})
                {
                    glPushMatrix();
                    glTranslatef(x, -0.3f, z);
                    glRotatef(90, 0.0f, 1.0f, 0.0f);
                    glutSolidTorus(0.1f, 0.2f, 20, 20);
                    glPopMatrix();
                }
            }*/

           // Front Left Wheel
            glPushMatrix();
            glTranslatef(-0.6f, -0.3f, 0.9f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glutSolidTorus(0.1f, 0.3f, 20, 20);
            glPopMatrix();

            // Front Right Wheel
            glPushMatrix();
            glTranslatef(0.6f, -0.3f, 0.9f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glutSolidTorus(0.1f, 0.3f, 20, 20);
            glPopMatrix();

            // Rear Left Wheel
            glPushMatrix();
            glTranslatef(-0.6f, -0.3f, -0.9f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
            glutSolidTorus(0.1f, 0.3f, 20, 20);
            glPopMatrix();

            // Rear Right Wheel
            glPushMatrix();
            glTranslatef(0.6f, -0.3f, -0.9f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
            glutSolidTorus(0.1f, 0.3f, 20, 20);
            glPopMatrix();

        };


        void drawWindows()
        {
            glColor4fv(windowColor);

            // Front Window
            glPushMatrix();
            glTranslatef(0.0f, 0.35f, 0.5f);
            glScalef(1.0f, 0.5f, 0.05f);
            glutSolidCube(1.0f);
            glPopMatrix();

            // Back Window
            glPushMatrix();
            glTranslatef(0.0f, 0.35f, -0.5f);
            glScalef(1.0f, 0.5f, 0.05f);
            glutSolidCube(1.0f);
            glPopMatrix();

            // Left Window
            glPushMatrix();
            glTranslatef(-0.75f, 0.35f, 0.0f);
            glScalef(0.05f, 0.5f, 1.0f);
            glutSolidCube(1.0f);
            glPopMatrix();

            // Right Window
            glPushMatrix();
            glTranslatef(0.75f, 0.35f, 0.0f);
            glScalef(0.05f, 0.5f, 1.0f);
            glutSolidCube(1.0f);
            glPopMatrix();


        }

        void drawHeadlights()
        {
            glColor3f(1.0f, 1.0f, 0.0f);

            // Left Headlight
            glPushMatrix();
            glTranslatef(-0.5f, -0.1f, 0.55f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();

            // Right Headlight
            glPushMatrix();
            glTranslatef(0.5f, -0.1f, 0.55f);
            glutSolidSphere(0.1f, 20, 20);
            glPopMatrix();

        }
};




class Simulation{
    private: 
        City city;
        Car car;

    public:
        City& getCity()
        {
            return city;
        }

        Car& getCar()
        {
            return car;
        }

        void display()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();


            gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

            city.drawGrid();

            //Car
            glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            car.draw();
            glPopMatrix();


            glutSwapBuffers();
        }
};


// global variable
Simulation simulation;


void displayCallback()
{
    //std::cout << "Rendering scen..." << std::endl;
    simulation.display();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    simulation.getCity().drawGrid();


    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    simulation.getCar().draw();
    glPopMatrix();

    simulation.getCar().applyFriction();
    simulation.display();

    glutSwapBuffers();


}

void keyboardCallback(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': // Move forward
        simulation.getCar().moveForward();
        break;
    case 's': // Move backward
        simulation.getCar().moveBackward();
        break;
    case 'a': // Rotate left
        simulation.getCar().rotate(5.0f);
        break;
    case 'd': // Rotate right
        simulation.getCar().rotate(-5.0f);
        break;
    case 27: // Escape key
        exit(0);
        break;
    }
    glutPostRedisplay();
}


void initOpenGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);//Background color GREY
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.33, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("City Simulation");
    glutKeyboardFunc(keyboardCallback);

    initOpenGL();

    glutDisplayFunc(displayCallback);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glutMainLoop();


    return 0;
}
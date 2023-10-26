from pymol.extensions.rep import PyMolRep

from OpenGL.GL import (glColor3f, glPushMatrix, glPopMatrix, glTranslatef)
from OpenGL.GLU import (gluCylinder, gluNewQuadric)

class RepArrow(PyMolRep):

    def render(self, context):
        for [x,y,z] in context.current_scene_coords():
            #glClear(GL_COLOR_BUFFER_BIT)
            glColor3f(0.0, 1.0, 1.0)
            glPushMatrix()
            glTranslatef(x,y,z)
            gluCylinder(gluNewQuadric(), 0.05, 0.05, 5, 32, 32)
            glPopMatrix()
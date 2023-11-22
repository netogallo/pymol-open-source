import math
from pymol.extensions.rep import PyMolRep

from OpenGL.GL import (glColor3f, glPushMatrix, glPopMatrix, glRotatef, glTranslatef)
from OpenGL.GLU import (gluCylinder, gluNewQuadric, gluSphere)

class RepArrow(PyMolRep):

    def __init__(self, x: float, y: float, z: float):
        super().__init__()
        self.__x = x
        self.__y = y
        self.__z = z
        self.__quadric = None

    @staticmethod
    def __angle__(sgn, dir, x, z):
        angle = \
            math.copysign(
                math.acos(abs(x) / math.sqrt(x**2 + z**2)),
                z*sgn
            )
        return math.copysign(
            math.degrees((math.pi / 2) + angle),
            x*dir
        )

    def render(self, context):

        #atoms = context.atoms()
        quadric = self.__quadric
        if quadric is None:
            quadric = self.__quadric = gluNewQuadric()
        try:
            glPushMatrix()
            glColor3f(1.0, 0.0, 0.0)
            glTranslatef(self.__x, self.__y, self.__z)
            gluSphere(quadric, 1, 32, 32)

        finally:
            glPopMatrix()

        glColor3f(0.0, 1.0, 0.0)
        for [x,y,z] in context.current_scene_coords():

            try:
                glPushMatrix()
                glTranslatef(x,y,z)
                dx, dy, dz = self.__x - x, self.__y - y, self.__z - z
                rot_x, rot_y, rot_z = 0*dz - 1*dy, 1*dx - 0*dz, 0*dy - 0*dy
                rot_angle = math.acos((0*dx + 0*dy + 1*dz) / (math.sqrt(dx**2 + dy**2 + dz**2)))
                
                glRotatef(math.degrees(rot_angle), rot_x, rot_y, rot_z)

                norm = math.sqrt(dx**2 + dy**2 + dz**2)
                gluCylinder(quadric, 0.05, 0.05, norm, 32, 32)

            finally:
                glPopMatrix()
#ifndef CAMERA_ORIGIN_H
#define CAMERA_ORIGIN_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
//y轴偏航
const float YAW         = 90.0f;
//x轴仰俯
const float PITCH       =  0.0f;

const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  30.0f;
const glm::vec3 TARGET_ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);

namespace glcar {

    //目标坐标原点的相机
    class CameraOrigin
    {
    private:
        /* data */
    public:
        //相机属性
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        //角度
        float yaw;
        float pitch;

        //灵敏度
        float mouseSensitivity; 
        float moveSpeed;
        float zoom;

        CameraOrigin(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 up = glm::vec3(0.0f, 0.1f, 0.0f), 
            float yaw = YAW, 
            float pitch = PITCH) 
            : 
            position(position),
            up(up),
            yaw(yaw),
            pitch(pitch),
            moveSpeed(SPEED),
            mouseSensitivity(SENSITIVITY),
            zoom(ZOOM)
        {

            worldUp = up;
            updateCameraVectors();

        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= mouseSensitivity;
            yoffset *= mouseSensitivity;

            yaw   += xoffset;
            pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            // if (constrainPitch)
            // {
            //     if (pitch > 89.0f)
            //         pitch = 89.0f;
            //     if (pitch < -89.0f)
            //         pitch = -89.0f;
            // }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset)
        {
            zoom -= (float)yoffset;
            if (zoom < 1.0f)
                zoom = 1.0f;
            if (zoom > 45.0f)
                zoom = 45.0f; 

            updateCameraVectors();
        }

        glm::mat4 getViewMatrix()
        {
            return glm::lookAt(position, TARGET_ORIGIN, up);
        }
    
    private:

        void updateCameraVectors()
        {
            if (pitch > 360) {
                pitch -= 360;
            }
            glm::vec3 newDirection;

            float pCos = cos(glm::radians(pitch));
            float ySin = sin(glm::radians(yaw));
            float yCos = cos(glm::radians(yaw));
            
            // //相机方向
            if ((pitch > 90  && pitch <  270)) {
                up = glm::vec3(0.0f, -0.1f, 0.0f);
            } else {
                up = glm::vec3(0.0f, 0.1f, 0.0f);
            }
        
            newDirection.x = yCos * pCos;
            newDirection.z = sin(glm::radians(yaw)) * pCos;
            newDirection.y = sin(glm::radians(pitch)); 

            //newDirection = glm::normalize(newDirection);

            // right = glm::normalize(glm::cross(newDirection, worldUp));
            // up = glm::normalize(glm::cross(right, newDirection));

            position = newDirection * zoom;

        }
    };
}

#endif
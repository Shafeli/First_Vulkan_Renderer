#pragma once
#include <glm/geometric.hpp>
#include <SDL2/SDL.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
    static constexpr float kYaw = -90.0f;
    static constexpr float kPitch = 0.0f;
    static constexpr float kMovementSpeed = 2.5f;
    static constexpr float kRotationSpeed = 9.5f;

    static constexpr float kMaxPitch = 89.0f; // Clamp values to prevent gimbal lock 
    static constexpr float kMinPitch = -89.0f;

    float m_yaw = kYaw;
    float m_pitch = kPitch;
    float m_movementSpeed = kMovementSpeed;
    float m_rotationSpeed = kMovementSpeed;

    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    void ResetPosition()
    {
        m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    void ResetFront()
    {
        m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    void ResetUp()
    {
        m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void ProcessPosition(const Uint8* keystate, float deltaTime)
    {
        float velocity = m_movementSpeed * deltaTime;

        if (keystate[SDL_SCANCODE_W])
            m_position += m_front * velocity;

        if (keystate[SDL_SCANCODE_S])
            m_position -= m_front * velocity;

        if (keystate[SDL_SCANCODE_A]) 
            m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity;

        if (keystate[SDL_SCANCODE_D])
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity;

        if (keystate[SDL_SCANCODE_SPACE])
            m_position += m_up * velocity;

        if (keystate[SDL_SCANCODE_LCTRL])
            m_position -= m_up * velocity;

        if (keystate[SDL_SCANCODE_DOWN])
            ResetPosition();

        if (keystate[SDL_SCANCODE_UP])
            ResetUp();

        if (keystate[SDL_SCANCODE_RIGHT])
            ResetFront();
    }
    
    void ProcessYawAndPitchMovement(const Uint8* keystate, float deltaTime)
    {
        const float velocity = m_rotationSpeed * deltaTime;

        if (keystate[SDL_SCANCODE_W])
            m_pitch += velocity;  // Look up
            

        if (keystate[SDL_SCANCODE_S])
            m_pitch -= velocity;  // Look down
            

        if (keystate[SDL_SCANCODE_A])
            m_yaw += velocity;  // Rotate left
            

        if (keystate[SDL_SCANCODE_D])
            m_yaw -= velocity;  // Rotate right
            

        // Clamp to prevent gimbal lock
        if (m_pitch > kMaxPitch) m_pitch = kMaxPitch;
        if (m_pitch < -kMaxPitch) m_pitch = -kMaxPitch;

        glm::vec3 front;

        // cos(yaw) * cos(pitch)
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        // sin(pitch)
        front.y = sin(glm::radians(m_pitch));

        // sin(yaw) * cos(pitch)
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = normalize(front);
    }
};


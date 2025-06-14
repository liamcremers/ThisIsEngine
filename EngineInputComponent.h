#pragma once
#include "BaseComponent.h"

namespace dae
{

    class EngineInputComponent : public BaseComponent
    {
    public:
        explicit EngineInputComponent(GameObject& pOwner) :
            BaseComponent(pOwner)
        {}

        virtual void Deactivate()
        {
            if (m_Enabled)
            {
                UnregisterCommands();
                m_Enabled = false;
            }
        }

        virtual void Activate()
        {
            if (!m_Enabled)
            {
                RegisterCommands();
                m_Enabled = true;
            }
        }

        virtual bool IsEnabled() const { return m_Enabled; }

    protected:
        virtual void RegisterCommands() = 0;
        virtual void UnregisterCommands() = 0;
        bool m_Enabled = true;
    };
}
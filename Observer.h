#pragma once
#include <list>
#include <string>
#include <any>

namespace dae
{
    class Observer;

    class Subject final
    {
    public:
        Subject() = default;
        ~Subject();

        void AddObserver(Observer* observer);
        void RemoveObserver(Observer* observer);
        void Notify(const std::string& eventId,
                    const std::any& args = std::any{});

        Subject(const Subject& other) = delete;
        Subject(Subject&& other) = delete;
        Subject& operator=(const Subject& other) = delete;
        Subject& operator=(Subject&& other) = delete;

    private:
        std::list<Observer*> m_ObserverList{};
    };

    class Observer
    {
        friend class Subject;

    protected:
        Observer() = default;
        virtual void OnNotify(
            const std::string& eventId,
            [[maybe_unused]] const std::any& args = std::any{}) = 0;
        virtual void OnDestroy() = 0;
    };
}

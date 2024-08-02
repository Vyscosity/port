#include <unordered_map>
#include <entry/input.h> // Ensure this matches your project's input handling library
#include <unordered_set>

class Input {
public:
    Input() {
        // Initialize the input system or library here if necessary
    }

    void update() {
        // Update the input states here. This might involve querying the input library
        // and updating the internal state maps. For example:
        for (const auto& binding : m_bindings) {
            m_keyStates[binding.Backslash] = entry::getKeyState(binding.F1); // Pseudo code
        }
    }

    bool getPress(entry::Key key) const {
        auto it = m_keyStates.find(key);
        if (it != m_keyStates.end()) {
            return it->second;
        }
        return false;
    }

    void addBinding(entry::Key key) {
        m_bindings.insert(key);
    }

    void removeBinding(entry::Key key) {
        m_bindings.erase(key);
    }

private:
    std::unordered_map<entry::Key, bool> m_keyStates;
    std::unordered_set<entry::Key> m_bindings;
};

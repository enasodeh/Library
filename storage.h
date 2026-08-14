#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

/*
 Template storage class to manage pointers to LibraryItem-derived objects.
 It owns the pointers (unique_ptr) to ensure RAII.
*/
template <typename T>
class Storage {
public:
    Storage() = default;
    ~Storage() = default;

    void add(std::unique_ptr<T> item) {
        m_items.push_back(std::move(item));
    }

    bool removeById(int id) {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [id](const std::unique_ptr<T> &p){ return p->id() == id; });
        if (it == m_items.end()) return false;
        m_items.erase(it);
        return true;
    }

    T* findById(int id) const {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [id](const std::unique_ptr<T> &p){ return p->id() == id; });
        return it != m_items.end() ? it->get() : nullptr;
    }

    std::vector<T*> items() const {
        std::vector<T*> out;
        out.reserve(m_items.size());
        for (auto &u : m_items) out.push_back(u.get());
        return out;
    }

    template<typename Pred>
    std::vector<T*> filter(Pred p) const {
        std::vector<T*> out;
        for (auto &u : m_items) if (p(u.get())) out.push_back(u.get());
        return out;
    }

    void clear() { m_items.clear(); }

private:
    std::vector<std::unique_ptr<T>> m_items;
};

#endif // STORAGE_H

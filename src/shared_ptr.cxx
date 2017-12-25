#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

struct Info
{
    Info(int id, std::string name)
        : m_id{id}
        , m_name{std::move(name)}
    {
    }
    int m_id;
    std::string m_name;
};

struct Collection
{
    Collection(std::string name, std::vector<Info> infos)
        : m_name{std::move(name)}
        , m_infos{std::move(infos)}
    {
    }
    std::string m_name;
    std::vector<Info> m_infos;
};

const std::shared_ptr<Info> get_info(const std::shared_ptr<Collection>& collection, size_t idx)
{
    // shared_ptr aliased constructor
    return std::shared_ptr<Info>(collection, &collection->m_infos[idx]);
}

std::ostream& operator<<(std::ostream& out, const Info& info)
{
    return out << "Info: {" << info.m_id << ", " << info.m_name << "}";
}

void show_info(const std::shared_ptr<Info>& i)
{
    std::cout << *i << '\n';
}

void print_info_n_times(const std::shared_ptr<Info>& info, size_t n)
{
    for (auto i = size_t{0}; i < n; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
        std::cout << *info << '\n';
    }
}

int main()
{
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    auto c = std::weak_ptr<Collection>{};
    {
        auto collection = std::make_shared<Collection>(
            "answers"s,
            std::vector<Info>{
                {42, "The answer"},
                {7, "Lucky number"},
                {13, "Unlucky number"},
            }
        );
        std::cout << "Collection use count (initially)      : "
                  << collection.use_count() << '\n';

        auto info = get_info(collection, 1);
        std::cout << "Collection use count (after get_info) : "
                  << collection.use_count() << '\n';

        c = collection;
        std::thread printer{print_info_n_times, info, 20};
        printer.detach();
    }

    std::cout << "collection scope ended\n";
    std::this_thread::sleep_for(1s);

    if (auto collection = c.lock())
    {
        std::cout << "Collection is still alive; use count: "
                  << collection.use_count()
                  << '\n';
    }
}


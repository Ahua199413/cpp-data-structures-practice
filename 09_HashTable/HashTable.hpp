#pragma once
#include <vector>
#include <stdexcept>
#include <functional> // 用於 std::hash

template <typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
public:
    enum State { EMPTY, OCCUPIED, DELETED };
    
    struct Entry {
        K key;
        V value;
        State state = EMPTY;
    };

private:
    std::vector<Entry> table_;
    size_t size_;               // 儲存的有效元素數量 (OCCUPIED)
    double max_load_factor_;    // 最大負載因子 (通常設為 0.7 到 0.75)
    Hash hash_func_;            // 雜湊函數

    // 取得雜湊 Index
    size_t getIndex(const K& key) const {
        return hash_func_(key) % table_.size();
    }

    // 重新調整大小並 Rehashing (擴容)
    void rehash();

public:
    // 建構子
    HashTable(size_t initial_capacity = 8, double max_load_factor = 0.7)
        : table_(initial_capacity), size_(0), max_load_factor_(max_load_factor){}

    ~HashTable() = default;

    bool insert(const K& key, const V& value);
    bool remove(const K& key);
    bool search(const K& key, V& value) const;

    size_t size() const { return size_; }
    bool isEmpty() const { return size_ == 0; }
    double loadFactor() const { return static_cast<double>(size_) / table_.size(); }        
};

// ----------------------------------------------------------------
// 模板成員函式實作
// ----------------------------------------------------------------
template <typename K, typename V, typename Hash>
bool HashTable<K, V, Hash>::insert(const K& key, const V& value) {
    // 啟用自動擴容
    if (loadFactor() >= max_load_factor_) { 
        rehash(); 
    }
    size_t index = getIndex(key);
    size_t i = index;
    int first_deleted_idx = -1; // 記錄第一個看到的 DELETED 位址

    do {
        if (table_[i].state == EMPTY) {
            // 沒找到重複的，直接插入到找到的第一個 DELETED 位址，若無則插入此 EMPTY 位址
            size_t target = (first_deleted_idx != -1) ? first_deleted_idx : i;
            table_[target] = {key, value, OCCUPIED};
            size_++;
            return true;
        } 
        else if (table_[i].state == DELETED) {
            if (first_deleted_idx == -1) first_deleted_idx = i;
        } 
        else if (table_[i].key == key) {
            // 找到重複的，更新並返回
            table_[i].value = value;
            return false;
        }
        i = (i + 1) % table_.size();
    } while (i != index);

    // 如果陣列全滿，且中間有經過 DELETED 位址，則插入
    if (first_deleted_idx != -1) {
        table_[first_deleted_idx] = {key, value, OCCUPIED};
        size_++;
        return true;
    }

    throw std::runtime_error("HashTable is full!");
}

template <typename K, typename V, typename Hash>
bool HashTable<K, V, Hash>::search(const K& key, V& value) const {
    size_t index = getIndex(key);
    size_t i = index;

    do {
        if (table_[i].state == EMPTY) {
            return false;
        }
        if (table_[i].state == OCCUPIED && table_[i].key == key) {
            value = table_[i].value;
            return true;
        }
        i = (i + 1) % table_.size();
    } while (i != index);

    return false;
}

template <typename K, typename V, typename Hash>
bool HashTable<K, V, Hash>::remove(const K& key) {
    size_t index = getIndex(key);
    size_t i = index;
    do {
        if (table_[i].state == EMPTY) {
            return false; // 遇空即停
        }
        if (table_[i].state == OCCUPIED && table_[i].key == key) {
            table_[i].state = DELETED; // 設為墓碑
            size_--;
            return true;
        }
        i = (i + 1) % table_.size();
    } while (i != index);
    return false;
}

template <typename K, typename V, typename Hash>
void HashTable<K, V, Hash>::rehash() {
    std::vector<Entry> oldTable = table_;
    size_t newCapacity = table_.size() * 2;
    
    // 1. 初始化一個兩倍大的全新 vector (狀態預設皆為 EMPTY)
    table_ = std::vector<Entry>(newCapacity);

    // 2. 重置 size_，因為下面的 insert() 會重新把 size_ 加回去
    size_ = 0;
    // 3. 將舊表中所有有效資料重新 insert
    for (const auto& entry : oldTable) {
        if (entry.state == OCCUPIED) {
            insert(entry.key, entry.value);
        }
    }
}
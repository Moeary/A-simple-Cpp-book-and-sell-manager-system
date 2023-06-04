class order {
    private:
        std::string m_buyerID;
        std::vector<std::string> m_bookIDs;
        std::time_t m_time;
    public:
        order(std::string buyerID, std::vector<std::string> bookIDs): m_buyerID(buyerID), m_bookIDs(bookIDs), m_time(std::time(nullptr)) {}
        order(std::string buyerID, std::vector<std::string> bookIDs,std::time_t t_time): m_buyerID(buyerID), m_bookIDs(bookIDs), m_time(t_time) {}
        std::string getBuyerID() const { return m_buyerID; }
        std::vector<std::string> getBookIDs() const { return m_bookIDs; }
        std::time_t getTime() const { return m_time; }
};
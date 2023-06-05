class order {
    private:
        string m_buyerID;
        vector<string> m_bookIDs;
        time_t m_time;
    public:
        order(string buyerID, vector<string> bookIDs): m_buyerID(buyerID), m_bookIDs(bookIDs), m_time(time(nullptr)) {}
        order(string buyerID, vector<string> bookIDs,time_t t_time): m_buyerID(buyerID), m_bookIDs(bookIDs), m_time(t_time) {}
        string getBuyerID() const { return m_buyerID; }
        vector<string> getBookIDs() const { return m_bookIDs; }
        time_t getTime() const { return m_time; }
};
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "test1.h"

class DemocraticSystem;

class DemocraticAction {
public:
    virtual void apply(DemocraticSystem& d) = 0;
    virtual std::string description() const = 0;
    virtual ~DemocraticAction() {}
};

class VoterCountChange : public DemocraticAction {
    int newVoterCount;
public:
    VoterCountChange(int count) : newVoterCount(count) {}
    void apply(DemocraticSystem& d) override;
    std::string description() const override { return "Change voter count"; }
};

class PartyCountChange : public DemocraticAction {
    int newPartyCount;
public:
    PartyCountChange(int count) : newPartyCount(count) {}
    void apply(DemocraticSystem& d) override;
    std::string description() const override { return "Change party count"; }
};

class LeaderChange : public DemocraticAction {
    std::string newLeader;
public:
    LeaderChange(const std::string& leader) : newLeader(leader) {}
    void apply(DemocraticSystem& d) override;
    std::string description() const override { return "Change leader"; }
};

class DemocraticSystem {
    std::string countryName;
    int voterCount;
    int partyCount;
    std::string currentLeader;
    std::vector<DemocraticAction*> actions;

public:
    DemocraticSystem(const std::string& name, int voters, int parties, const std::string& leader,
                     const std::vector<DemocraticAction*>& plan = {})
        : countryName(name), voterCount(voters), partyCount(parties), currentLeader(leader), actions(plan) {}

    std::string getCountryName() const { return countryName; }
    int getVoterCount() const { return voterCount; }
    int getPartyCount() const { return partyCount; }
    std::string getLeader() const { return currentLeader; }

    void setVoterCount(int v) { voterCount = v; }
    void setPartyCount(int p) { partyCount = p; }
    void setLeader(const std::string& l) { currentLeader = l; }

    double votersPerParty() const {
        if (partyCount == 0) return 0;
        return static_cast<double>(voterCount) / partyCount;
    }

    void executeActions() {
        for (auto* act : actions)
            act->apply(*this);
    }

    void display() const {
        std::cout << "Country: " << countryName
                  << "\nVoter Count: " << voterCount
                  << "\nParty Count: " << partyCount
                  << "\nCurrent Leader: " << currentLeader << "\n";
    }

    ~DemocraticSystem() {
        for (auto* act : actions)
            delete act;
    }

    DemocraticSystem(const DemocraticSystem&) = delete;
    DemocraticSystem& operator=(const DemocraticSystem&) = delete;
};

void VoterCountChange::apply(DemocraticSystem& d) { d.setVoterCount(newVoterCount); }
void PartyCountChange::apply(DemocraticSystem& d) { d.setPartyCount(newPartyCount); }
void LeaderChange::apply(DemocraticSystem& d) { d.setLeader(newLeader); }

TEST(DemocracyTest, VotersPerPartyCheck) {
    std::vector<DemocraticAction*> plan;
    DemocraticSystem d("Freedonia", 5000000, 5, "John Doe", plan);
    ASSERT_EQ(d.votersPerParty(), 1000000);
    return true;
}

TEST(DemocracyTest, LeaderChangeAction) {
    std::vector<DemocraticAction*> plan = { new LeaderChange("Alice Smith") };
    DemocraticSystem d("Libertania", 2000000, 4, "Bob Brown", plan);
    d.executeActions();
    ASSERT_EQ(d.getLeader(), "Alice Smith");
    return true;
}

TEST(DemocracyTest, PartyChangeAffectsVotersRatio) {
    std::vector<DemocraticAction*> plan = { new PartyCountChange(10) };
    DemocraticSystem d("MultiPartyLand", 1000000, 5, "Leader A", plan);
    double oldRatio = d.votersPerParty();
    d.executeActions();
    ASSERT_TRUE(d.votersPerParty() < oldRatio);
    return true;
}

TEST(DemocracyTest, DirectVoterUpdate) {
    DemocraticSystem d("VoteNation", 1000000, 2, "Leader X");
    d.setVoterCount(3000000);
    ASSERT_EQ(d.getVoterCount(), 3000000);
    return true;
}

TEST(DemocracyTest, ZeroParties) {
    DemocraticSystem d("NoPartyLand", 1000000, 0, "Leader Z");
    ASSERT_EQ(d.votersPerParty(), 0);
    return true;
}

TEST(DemocracyTest, CountryNameCheck) {
    DemocraticSystem d("Electoria", 1500000, 3, "Leader Y");
    ASSERT_EQ(d.getCountryName(), "Electoria");
    return true;
}

TEST(DemocracyTest, VotersPerPartyLargeValues) {
    DemocraticSystem d("MegaDemocracy", 1e8, 100, "Big Leader");
    ASSERT_TRUE(std::abs(d.votersPerParty() - (1e8 / 100)) < 1e-6);
    return true;
}

TEST(DemocracyTest, MultipleActionsTest) {
    std::vector<DemocraticAction*> plan = {
        new VoterCountChange(2500000),
        new PartyCountChange(8),
        new LeaderChange("Leader New")
    };
    DemocraticSystem d("Reformia", 1000000, 5, "Old Leader", plan);
    d.executeActions();
    ASSERT_EQ(d.getVoterCount(), 2500000);
    ASSERT_EQ(d.getPartyCount(), 8);
    ASSERT_EQ(d.getLeader(), "Leader New");
    return true;
}

TEST(DemocracyTest, ZeroVotersCheck) {
    DemocraticSystem d("EmptyVotes", 0, 4, "NoVote Leader");
    ASSERT_EQ(d.votersPerParty(), 0);
    return true;
}

int main() {
    RUN_TEST(DemocracyTest, VotersPerPartyCheck);
    RUN_TEST(DemocracyTest, LeaderChangeAction);
    RUN_TEST(DemocracyTest, PartyChangeAffectsVotersRatio);
    RUN_TEST(DemocracyTest, DirectVoterUpdate);
    RUN_TEST(DemocracyTest, ZeroParties);
    RUN_TEST(DemocracyTest, CountryNameCheck);
    RUN_TEST(DemocracyTest, VotersPerPartyLargeValues);
    RUN_TEST(DemocracyTest, MultipleActionsTest);
    RUN_TEST(DemocracyTest, ZeroVotersCheck);
    return 0;
}

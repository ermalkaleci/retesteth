#pragma once
#include <libdataobj/DataObject.h>
#include <retesteth/session/SessionInterface.h>
#include <retesteth/testStructures/types/BlockchainTests/BlockchainTestFiller.h>
#include "TestBlockchainManager.h"

namespace test::blockchainfiller
{
class BlockchainTestFillerRunner
{
public:
    BlockchainTestFillerRunner(teststruct::BlockchainTestInFiller const&);
    ~BlockchainTestFillerRunner() {};
    dataobject::spDataObject result() { return m_result; }

    bool checkSinglenet(teststruct::FORK const& _net) const;
    dataobject::spDataObject makeNewBCTestForNet(teststruct::FORK const& _net);
    TestBlockchainManager makeTestChainManager(teststruct::FORK const& _net);
    void makeGenesis(spDataObject& _filler, TestBlockchainManager& _testchain) const;
    void setTestInfoAndExpectExceptions(teststruct::FORK const& _net) const;
    bool optionsLimitBlock(size_t _block) const;
    void performOptionsOnFinalState(EthGetBlockBy const&);
    void compareFinalState(spDataObject& _filledTest, StateIncomplete const& _expectState, EthGetBlockBy const&);
    EthGetBlockBy getLastBlock();

private:
    test::teststruct::BlockchainTestInFiller const& m_test;
    test::session::SessionInterface& m_session;
    dataobject::spDataObject m_result;
};

}  // namespace test

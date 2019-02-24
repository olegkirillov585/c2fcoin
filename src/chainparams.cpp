// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The C2FCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
		    (0, uint256("000007a57161d356ea40900e67fcdd22f3ea2209e25845b10fb8ff18fb9c6f0e"))
			(100, uint256("00000099131a37e2465b66ae7372a6b487870f4354a8299177c3417c64f0cc42"))
			(200, uint256("000001f90c2b0d89d4e243e8c0ef749ae8b9dc61d464c3b7647f6d55c0c67dab"))
	        (270, uint256("8f4efabf11b711160feb224bb07bf85d066a5ddd270d01d5eabdf165cdb1c17e"))
	        (500, uint256("2d00010df574ac95a532dcf9aae16d270e1c6c7e6b79bb7f657e777726e71595"))
	        (1000, uint256("e709d95632f8090e5ad24a980764e320cf24885073c669dbe97a66944bdf5bbe"))
	        (5000, uint256("b40912b73cae77af5cb1f020c3c8b13eb981f5f0a1f79ce5acab99d0e228ff3e"))
	        (10000, uint256("3a90595014e997c5c6e2ffbe4283090fb9ee6cc4c9687c58c3ab1f75e4303fb3"))
	        (25000, uint256("7f970b0e90d2833cf0204647d86d2e5e5c8195840964a4058fa3510bd937e1fe"))
	        (50000, uint256("05eef6a92922257d42e19646f7d4d6c7aab9dc9e61b76d70b3c014e7bc6d9000"))
	        (75000, uint256("d3d281551ba9627e6735b5b175f42a7a7de52378b9f629ed8125d56e17a63edd"))
	        (92512, uint256("b98c634040e4c585cb07c86ed6baf21724234d9279cd46e99852df3790233af9")); 

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1537564881, // * UNIX timestamp of last checkpoint block
        346,       // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
                (       0, uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"))
				;        // First PoW block
				
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1537564881,
        0,
        2000
		};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1537564881,
    0,
    100
	};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x63;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x84;
        vAlertPubKey = ParseHex("0469058ddd90fe895e11d175ebcc79259d506c01c15a135387dbc315d645df08ffe7b01f196587857738a91094833722e7561d348fe5efcc2ac1d51ac60b436259");
        nDefaultPort = 13131;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // C2FCoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;       // Halving interval
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;                      // Obsolete (**TODO**)
        nTargetTimespan = 1 * 60;               // C2FCoin: 1 minute
        nTargetSpacing = 1 * 60;                // C2FCoin: 1 minute
        nMaturity = 25;                         // Block maturity
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 20000000 * COIN;        // Large number effectively unlimited. Will deprecate TODO
        nMasternodeCollateral = 1000;          // Masternode Collateral requirement
        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;                  //
        nModifierUpdateBlock = 1100;            // Modify block on height
        nZerocoinStartHeight = 9900000;         // DISABLED FOR NOW TODO Zerocoin start height
        nZerocoinStartTime = 1546300800;        // Saturday, Jan 1, 2019 00:00:00 AM (GMT)
        nBlockEnforceSerialRange = 1;           // Enforce serial range starting this block
        nBlockRecalculateAccumulators = 100000; // Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 1110;           // 1110; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = 1001;        // Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 1000;        // Start enforcing the invalid UTXO's

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "C2FCoin Coin Mainnet Launch";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 3;
        genesis.nTime = 1537564881;  // Friday 21 September 2018 21:21:21 GMT
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1767948;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("000007a57161d356ea40900e67fcdd22f3ea2209e25845b10fb8ff18fb9c6f0e"))
        {
            printf("MAINNET: Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("MAINNET: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("000007a57161d356ea40900e67fcdd22f3ea2209e25845b10fb8ff18fb9c6f0e"));
        assert(genesis.hashMerkleRoot == uint256("3b1b8b41cd234fad0644f11522d71b372cb7eee05557e4b520e690b56c9df3f8"));

        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("94.180.247.7", "94.180.247.7"));
		//vSeeds.push_back(CDNSSeedData("185.87.193.127", "185.87.193.127"));
		//vSeeds.push_back(CDNSSeedData("185.87.193.141", "185.87.193.141"));
		//vSeeds.push_back(CDNSSeedData("185.87.193.144", "185.87.193.144"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); // addresses start with C
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 30); // scripts start with D
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 55); // private key start with P
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x25)(0x2d)(0x7d).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x64).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0x73).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04ee4aa867c97c17ac9f3495007901f64ad9c1e14cf88b4bb9f2721e912c74e43d91ed1da41753d5745b148514f8d6cedbd433fd5b2cba059326f0c66c2078922b";
        strObfuscationPoolDummyAddress = "CWBStDgeCUaYZ2DzAkSvNxr6ahRVuyGWec";
        nStartMasternodePayments = 1537564881; // GMT: 21 September 2018 21:21:21

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0x65;
        pchMessageStart[2] = 0x9e;
        pchMessageStart[3] = 0x87;
        vAlertPubKey = ParseHex("04dad852aab0fe56b56189f910eba2d8b76bf233493374e9dbbb33eeb8e48dec45b7e772f6017d5d0b9d3278b6a804323f2db0bc786164a553ed727dda0b5108be");
        nDefaultPort = 13231;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // C2FCoin: 1 minute
        nTargetSpacing = 1 * 60;  // C2FCoin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 5;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; // 
        nMaxMoneyOut = 20000000 * COIN;
        nZerocoinStartHeight = 250;
        nZerocoinStartTime = 1546300800; // Saturday, Jan 1, 2019 00:00:00 AM (GMT)
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1500; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 100000; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = 1001; //Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 1000; //Start enforcing the invalid UTXO's

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1537564881; 
        genesis.nNonce = 888950;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"))
        {
            printf("TESTNET: Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("TESTNET: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"));
		// assert(genesis.hashMerkleRoot == uint256("a24fe577ebfa1041ba93d438302dfc8ecf47438a6bdc66edcab9d0267fe10781"));
		// merkle matches the mainnet - ok

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("149.28.82.70", "149.28.82.70"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87); // Testnet c2fcoin addresses start with 'c'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);  // Testnet c2fcoin script addresses start with 'd'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 117);     // Testnet private keys start with 'p'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0x7d).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0xef).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // we enable for test purpose low dif mining on main
        nPoolMaxTransactions = 2;
        strSporkKey = "0435f3871b668f1abba8b8ed01a881e3b211464cd8609a6c59adc92a9aa8c333a03a16ae17bcb583e8aa601d3cb6d662513a7c6d668ec88a397d0b1d22ae9c3954";
        strObfuscationPoolDummyAddress = "TMPUBzcsHZawA32XYYDF9FHQp6icv492CV";
        nStartMasternodePayments = 1529903701;  // GMT: 2018-06-09T00:00:00Z
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x76;
        pchMessageStart[1] = 0x12;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xfa;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // C2FCoin: 1 day
        nTargetSpacing = 1 * 60;        // C2FCoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1537564881; 
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 888950;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 13374;
        if(genesis.GetHash() != uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"))
        {
            printf("REGTEST: Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("REGTEST: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("REGTEST: \n block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("00000a654f1d86f4f6f7cdd8b664873b0f478d41d8627fe4e8c6c755fb911848"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

import FWCore.ParameterSet.Config as cms

process = cms.Process("RERECO")

### standard MessageLoggerConfiguration
process.load("FWCore.MessageService.MessageLogger_cfi")

### source
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            #  '/store/relval/CMSSW_7_0_0_pre11/RelValSingleMuPt10_UP15/GEN-SIM-RECO/POSTLS162_V4-v1/00000/D422D1A4-7F6A-E311-80D3-002590593872.root',
            #  '/store/relval/CMSSW_7_0_0_pre11/RelValSingleMuPt10_UP15/GEN-SIM-RECO/POSTLS162_V4-v1/00000/C2C7F39E-7F6A-E311-9176-002618943986.root',
            #  '/store/relval/CMSSW_7_0_0_pre11/RelValSingleMuPt10_UP15/GEN-SIM-RECO/POSTLS162_V4-v1/00000/90BFAC4A-876A-E311-8EE8-0025905A60A0.root',
            #  '/store/relval/CMSSW_7_0_0_pre11/RelValSingleMuPt10_UP15/GEN-SIM-RECO/POSTLS162_V4-v1/00000/64E0FC9E-7F6A-E311-A464-002618943986.root',
            #  '/store/relval/CMSSW_7_0_0_pre11/RelValSingleMuPt10_UP15/GEN-SIM-RECO/POSTLS162_V4-v1/00000/2CAA4F6B-8D6A-E311-806A-0026189438BA.root'
            ###################################
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/FAD4A66E-766A-E311-B952-003048FEAD24.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/F47668A7-716A-E311-BAFF-C860001BD8B2.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/F233BB1E-746A-E311-B887-003048CF92A4.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/D4A2F623-746A-E311-8276-0025904AC462.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/D26E4FD0-726A-E311-84A3-003048FEAF60.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/C81FB611-796A-E311-A180-0025904A8632.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/C69F08A8-716A-E311-BAC0-02163E00E729.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/A49D704B-716A-E311-B4EE-003048F11D56.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/9C7A752F-726A-E311-AA48-003048F17C08.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/9A11C1EE-776A-E311-A7DB-003048F1C580.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/98674021-726A-E311-9DE0-02163E00A3BF.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/96EA57E5-796A-E311-A235-002481E0DB70.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/8A8C9E02-7B6A-E311-9CB4-0025901AF6A4.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/78AFF593-776A-E311-8901-001D09F2441B.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/72497178-746A-E311-B42B-C86000151BDE.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/6E79B5F3-746A-E311-A940-003048F1C996.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/6A5DBE52-736A-E311-97EA-003048C90FD2.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/62EEB3B5-736A-E311-AF95-0025904B11AA.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/5C9DA173-7E6A-E311-A915-BCAEC5364C93.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/40BADC7D-746A-E311-A359-02163E00E74A.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/3E27DC8E-716A-E311-858C-003048D2C17E.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/3C491FFF-756A-E311-A90F-02163E00CC89.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/20880C5B-786A-E311-AAD7-02163E00E6CF.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/1623789D-756A-E311-92A2-002590495244.root',
            #'/store/relval/CMSSW_7_0_0_pre11/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/08F10B4C-736A-E311-88F4-003048F1C41A.root'

            )
        )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# same as input file
#process.GlobalTag.globaltag = 'PRE_ST62_V8::All'
# or get it automatically
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')

### standard includes (can't live without)
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration.StandardSequences.Geometry_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

### define tracking sequences to run
# need to recreate hits from clusters (which are stored in RECO)
process.clustToHits = cms.Sequence(
        process.siPixelRecHits
        * process.siStripMatchedRecHits
        )

# this is the official tracking sequence
process.tracking = cms.Sequence(
        process.MeasurementTrackerEvent
        * process.trackingGlobalReco
        )

### define output EDMFile
MyReRecoEventContent = cms.PSet(
        outputCommands = cms.untracked.vstring(
            'drop *',
            'keep *_siPixelClusters_*_*',
            'keep *_siStripClusters_*_*',
            'keep *_offlineBeamSpot_*_*',
            'keep *_pixelVertices_*_*',
            'keep *_*_*_RERECO'),
        splitLevel = cms.untracked.int32(0),
        eventAutoFlushCompressedSize=cms.untracked.int32(5*1024*1024)
        )

process.out = cms.OutputModule("PoolOutputModule",
        MyReRecoEventContent,
        fileName = cms.untracked.string('RelValTTbar_13-GEN-SIM-RECO-PU25ns_POSTLS162_V4-v1.root')
        )

### paths
process.p = cms.Path(process.clustToHits * process.tracking)
process.o = cms.EndPath(process.out)

### sequence of paths to run
process.schedule = cms.Schedule(process.p,process.o)

### debug time and memory information (more at Validation/Performance/python//TimeMemory*.py)
#process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.SimpleMemoryCheck=cms.Service("SimpleMemoryCheck",
#                                      ignoreTotal=cms.untracked.int32(1),
#                                      oncePerEventMode=cms.untracked.bool(False))

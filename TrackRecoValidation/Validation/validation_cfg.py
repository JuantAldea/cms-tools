import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:reco_trk.root'
    )
)

process.demo = cms.EDAnalyzer('Validation', 
               tracks = cms.untracked.InputTag('generalTracks')
)

process.TFileService = cms.Service("TFileService",
               fileName = cms.string('trackAnalysis.root')
)

process.p = cms.Path(process.demo)

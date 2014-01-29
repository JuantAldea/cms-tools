import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('Validation'
     ,tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)

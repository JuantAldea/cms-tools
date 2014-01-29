#include <memory>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

class Validation : public edm::EDAnalyzer
{

public:
    explicit Validation(const edm::ParameterSet&);
    ~Validation();
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    edm::InputTag tracksTag_; //used to select what tracks to read from configuration file
    TH1I *h_track_trackerHits;
    TH1I *h_track_trackerExpectedHitsInner;
    TH1I *h_track_trackerExpectedHitsOuter;
    TH1I *h_track_trackerLayersWithMeasurement;
    int maxTrackerHits;
    int maxExpectedInner;
    int maxExpectedOuter;
    int maxSumAll;
    int maxTrackerValidHits;
};

Validation::Validation(const edm::ParameterSet& iConfig):
    tracksTag_(iConfig.getUntrackedParameter<edm::InputTag>("tracks")),
    maxTrackerHits(0),
    maxExpectedInner(0),
    maxExpectedOuter(0),
    maxSumAll(0),
    maxTrackerValidHits(0)

{
    edm::Service<TFileService> fs;

    h_track_trackerHits = fs->make<TH1I>("track_trackerHits", "track_trackerHits", 100, 0, 100);
    h_track_trackerExpectedHitsInner = fs->make<TH1I>("track_trackerExpectedHitsInner", "track_trackerExpectedHitsInner", 100, 0, 100);
    h_track_trackerExpectedHitsOuter = fs->make<TH1I>("track_trackerExpectedHitsOuter", "track_trackerExpectedHitsOuter", 100, 0, 100);

    h_track_trackerLayersWithMeasurement = fs->make<TH1I>("track_trackerLayersWithMeasurement", "track_trackerLayersWithMeasurement", 100, 0, 100);
}


Validation::~Validation()
{
    ;
}

// ------------ method called for each event  ------------
void Validation::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    using namespace edm;
    using namespace reco;
    using namespace std;

    Handle<TrackCollection> tracks;
    iEvent.getByLabel(tracksTag_, tracks);

    for (TrackCollection::const_iterator itTrack = tracks->begin(); itTrack != tracks->end(); ++itTrack) {
        HitPattern track_hitPattern = itTrack->hitPattern();
        HitPattern track_expectedHitsInner = itTrack->trackerExpectedHitsInner();
        HitPattern track_expectedHitsOuter = itTrack->trackerExpectedHitsOuter();

        h_track_trackerHits->Fill(track_hitPattern.numberOfHits());
        h_track_trackerExpectedHitsInner->Fill(track_expectedHitsInner.numberOfHits());
        h_track_trackerExpectedHitsOuter->Fill(track_expectedHitsOuter.numberOfHits());

        h_track_trackerLayersWithMeasurement->Fill(track_hitPattern.trackerLayersWithMeasurement());

        // numberOfHits() -> counts every pattern different than 0x0
        // https://cmssdt.cern.ch/SDT/lxr/source/DataFormats/TrackReco/src/HitPattern.cc#213

        if (maxTrackerHits < track_hitPattern.numberOfHits()) {
            maxTrackerHits = track_hitPattern.numberOfHits();
        }

        if (maxExpectedInner < track_expectedHitsInner.numberOfHits()) {
            maxExpectedInner = track_expectedHitsInner.numberOfHits();
        }

        if (maxExpectedOuter < track_expectedHitsOuter.numberOfHits()) {
            maxExpectedOuter = track_expectedHitsOuter.numberOfHits();
        }

        int sum =  track_hitPattern.numberOfHits() + track_expectedHitsInner.numberOfHits() + track_expectedHitsOuter.numberOfHits();
        if (maxSumAll < sum) {
            maxSumAll = sum;
        }

        if (maxTrackerValidHits < track_hitPattern.numberOfValidHits()) {
            maxTrackerValidHits = track_hitPattern.numberOfValidHits();
        }
    }
}


// ------------ method called once each job just before starting event loop  ------------
void Validation::beginJob()
{
    ;
}

// ------------ method called once each job just after ending the event loop  ------------
void Validation::endJob()
{
    using namespace std;
    cout << "maxTrackerHits " << maxTrackerHits << endl;
    cout << "maxExpectedInner " << maxExpectedInner << endl;
    cout << "maxExpectedOuter " << maxExpectedOuter << endl;
    cout << "maxSumAll " << maxSumAll << endl;
    cout << "maxTrackerValidHits " << maxTrackerValidHits << endl;
}

// ------------ method called when starting to processes a run  ------------
/*
void Validation::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void Validation::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void Validation::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void Validation::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void Validation::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);

    //Specify that only 'tracks' is allowed
    //To use, remove the default given above and uncomment below
    //ParameterSetDescription desc;
    //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
    //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Validation);

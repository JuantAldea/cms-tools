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
    //used to select what tracks to read from configuration file
    
    edm::InputTag tracksTag_; 
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
    ;
}


Validation::~Validation()
{
    ;
}

//#define NEW_CODE

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

        if (maxTrackerHits < track_hitPattern.numberOfHits()) {
            maxTrackerHits = track_hitPattern.numberOfHits();
        }

        if (maxExpectedInner < track_expectedHitsInner.numberOfHits()) {
            maxExpectedInner = track_expectedHitsInner.numberOfHits();
        }

        if (maxExpectedOuter < track_expectedHitsOuter.numberOfHits()) {
            maxExpectedOuter = track_expectedHitsOuter.numberOfHits();
        }

        int sum =  track_hitPattern.numberOfHits()
                   + track_expectedHitsInner.numberOfHits()
                   + track_expectedHitsOuter.numberOfHits();

        if (maxSumAll < sum) {
            maxSumAll = sum;
        
        }
        cout << "Patterns: ";
        track_hitPattern.print();
        cout << endl;

        int index = 0;
        uint32_t pattern = 0x0;
        while ((pattern =  track_hitPattern.getHitPattern(index)) != 0x0) {
            cout << "Index " << index << ' ';
            cout << HitPattern::trackerHitFilter(pattern) << ' ';
            cout << HitPattern::muonHitFilter(pattern) << ' ';
            cout << HitPattern::getSubStructure(pattern) << ' ';
            cout << HitPattern::pixelHitFilter(pattern) << ' ';
            cout << HitPattern::pixelBarrelHitFilter(pattern) << ' ';
            cout << HitPattern::pixelEndcapHitFilter(pattern) << ' ';
            cout << HitPattern::stripHitFilter(pattern) << ' ';
            cout << HitPattern::stripTIBHitFilter(pattern) << ' ';
            cout << HitPattern::stripTIDHitFilter(pattern) << ' ';
            cout << HitPattern::stripTOBHitFilter(pattern) << ' ';
            cout << HitPattern::stripTECHitFilter(pattern) << ' ';
            cout << HitPattern::muonDTHitFilter(pattern) << ' ';
            cout << HitPattern::muonCSCHitFilter(pattern) << ' ';
            cout << HitPattern::muonRPCHitFilter(pattern) << ' ';
            cout << HitPattern::getLayer(pattern) << ' ';
            cout << HitPattern::getSubSubStructure(pattern) << ' ';
            cout << HitPattern::getMuonStation(pattern) << ' ';
            cout << HitPattern::getDTSuperLayer(pattern) << ' ';
            cout << HitPattern::getCSCRing(pattern) << ' ';
            cout << HitPattern::getRPCLayer(pattern) << ' ';
            cout << HitPattern::getRPCregion(pattern) << ' ';
            cout << HitPattern::getHitType(pattern) << ' ';
            cout << HitPattern::validHitFilter(pattern) << ' ';
#ifdef NEW_CODE
            cout << HitPattern::missingHitFilter(pattern) << ' ';
            cout << HitPattern::inactiveHitFilter(pattern) << ' ';
            cout << HitPattern::badHitFilter(pattern) << ' ';
            //cout << HitPattern::expectedInnerHitFilter(pattern) << ' ';
            //cout << HitPattern::expectedOuterHitFilter(pattern) << ' ';
#else
            cout << HitPattern::type_1_HitFilter(pattern) << ' ';
            cout << HitPattern::type_2_HitFilter(pattern) << ' ';
            cout << HitPattern::type_3_HitFilter(pattern) << ' ';
#endif //NEW_CODE
            cout << HitPattern::getSide(pattern) << ' ';
            cout << endl;
            index++;
        }

        cout << "numberOfHits ";
        cout << track_hitPattern.numberOfHits();
        cout << endl;

        cout << "numberOfValidHits ";
        cout << track_hitPattern.numberOfValidHits() << ' ';
        cout << track_hitPattern.numberOfValidTrackerHits() << ' ';
        cout << track_hitPattern.numberOfValidMuonHits() << ' ';
        cout << track_hitPattern.numberOfValidPixelHits() << ' ';
        cout << track_hitPattern.numberOfValidPixelBarrelHits() << ' ';
        cout << track_hitPattern.numberOfValidPixelEndcapHits() << ' ';
        cout << track_hitPattern.numberOfValidStripHits() << ' ';
        cout << track_hitPattern.numberOfValidStripTIBHits() << ' ';
        cout << track_hitPattern.numberOfValidStripTIDHits() << ' ';
        cout << track_hitPattern.numberOfValidStripTOBHits() << ' ';
        cout << track_hitPattern.numberOfValidStripTECHits() << ' ';
        cout << track_hitPattern.numberOfValidMuonDTHits() << ' ';
        cout << track_hitPattern.numberOfValidMuonCSCHits() << ' ';
        cout << track_hitPattern.numberOfValidMuonRPCHits() << ' ';
        cout << endl;

        cout << "numberOfLostHits ";
        cout << track_hitPattern.numberOfLostHits() << ' ';
        cout << track_hitPattern.numberOfLostTrackerHits() << ' ';
        cout << track_hitPattern.numberOfLostMuonHits() << ' ';
        cout << track_hitPattern.numberOfLostPixelHits() << ' ';
        cout << track_hitPattern.numberOfLostPixelBarrelHits() << ' ';
        cout << track_hitPattern.numberOfLostPixelEndcapHits() << ' ';
        cout << track_hitPattern.numberOfLostStripHits() << ' ';
        cout << track_hitPattern.numberOfLostStripTIBHits() << ' ';
        cout << track_hitPattern.numberOfLostStripTIDHits() << ' ';
        cout << track_hitPattern.numberOfLostStripTOBHits() << ' ';
        cout << track_hitPattern.numberOfLostStripTECHits() << ' ';
        cout << track_hitPattern.numberOfLostMuonDTHits() << ' ';
        cout << track_hitPattern.numberOfLostMuonCSCHits() << ' ';
        cout << track_hitPattern.numberOfLostMuonRPCHits() << ' ';
        cout << endl;

        cout << "numberOfBadHits ";
        cout << track_hitPattern.numberOfBadHits() << ' ';
        cout << track_hitPattern.numberOfBadMuonHits() << ' ';
        cout << track_hitPattern.numberOfBadMuonDTHits() << ' ';
        cout << track_hitPattern.numberOfBadMuonCSCHits() << ' ';
        cout << track_hitPattern.numberOfBadMuonRPCHits() << ' ';
        cout << track_hitPattern.numberOfInactiveHits() << ' ';
        cout << track_hitPattern.numberOfInactiveTrackerHits() << ' ';
#ifdef NEW_CODE
        //cout << track_hitPattern.numberOfExpectedInnerHits() << ' ';
        //cout << track_hitPattern.numberOfExpectedOuterHits() << ' ';
#endif
        cout << endl;

        cout << " missing methods should be added here\n";
        // bunch of numberOfValid* missing and some more, jumping to With Measurement
        cout << track_hitPattern.numberOfValidStripLayersWithMonoAndStereo();
        cout << endl;

        cout << "layersWithMeasurements ";
        cout << track_hitPattern.trackerLayersWithMeasurement() << ' ';
        cout << track_hitPattern.pixelLayersWithMeasurement() << ' ';
        cout << track_hitPattern.stripLayersWithMeasurement() << ' ';
        cout << track_hitPattern.pixelBarrelLayersWithMeasurement() << ' ';
        cout << track_hitPattern.pixelEndcapLayersWithMeasurement() << ' ';
        cout << track_hitPattern.stripTIBLayersWithMeasurement() << ' ';
        cout << track_hitPattern.stripTIDLayersWithMeasurement() << ' ';
        cout << track_hitPattern.stripTOBLayersWithMeasurement() << ' ';
        cout << track_hitPattern.stripTECLayersWithMeasurement() << ' ';
        cout << endl;

        cout << "WithoutMeasurements ";
        cout << track_hitPattern.trackerLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.pixelLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.stripLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.pixelBarrelLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.pixelEndcapLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.stripTIBLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.stripTIDLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.stripTOBLayersWithoutMeasurement() << ' ';
        cout << track_hitPattern.stripTECLayersWithoutMeasurement() << ' ';
        cout << endl;
        
        cout << "LayersTotallyOffOrBad ";
        cout << track_hitPattern.trackerLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.pixelLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.stripLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.pixelBarrelLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.pixelEndcapLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.stripTIBLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.stripTIDLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.stripTOBLayersTotallyOffOrBad() << ' ';
        cout << track_hitPattern.stripTECLayersTotallyOffOrBad() << ' ';     
        cout << endl;

        cout << "LayersNull ";
        cout << track_hitPattern.trackerLayersNull() << ' ';
        cout << track_hitPattern.pixelLayersNull() << ' ';
        cout << track_hitPattern.stripLayersNull() << ' ';
        cout << track_hitPattern.pixelBarrelLayersNull() << ' ';
        cout << track_hitPattern.pixelEndcapLayersNull() << ' ';
        cout << track_hitPattern.stripTIBLayersNull() << ' ';
        cout << track_hitPattern.stripTIDLayersNull() << ' ';
        cout << track_hitPattern.stripTOBLayersNull() << ' ';
        cout << track_hitPattern.stripTECLayersNull() << ' ';
        cout << endl;

        //muon stations missing
        cout << "muon stuff ";
        cout << track_hitPattern.muonStationsWithValidHits() << ' ';
        cout << track_hitPattern.muonStationsWithBadHits() << ' ';
        cout << track_hitPattern.muonStationsWithAnyHits() << ' ';
        cout << track_hitPattern.dtStationsWithValidHits() << ' ';
        cout << track_hitPattern.dtStationsWithBadHits() << ' ';
        cout << track_hitPattern.dtStationsWithAnyHits() << ' ';
        cout << track_hitPattern.cscStationsWithValidHits() << ' ';
        cout << track_hitPattern.cscStationsWithBadHits() << ' ';
        cout << track_hitPattern.cscStationsWithAnyHits() << ' ';
        cout << track_hitPattern.rpcStationsWithValidHits() << ' ';
        cout << track_hitPattern.rpcStationsWithBadHits() << ' ';
        cout << track_hitPattern.rpcStationsWithAnyHits() << ' ';
        //missing  track_hitPattern.innermostMuonStationWithHits(int hitType)
        cout << track_hitPattern.innermostMuonStationWithValidHits() << ' ';
        cout << track_hitPattern.innermostMuonStationWithBadHits() << ' ';
        cout << track_hitPattern.innermostMuonStationWithAnyHits() << ' ';
        //missing cout << track_hitPattern.outermostMuonStationWithHits(int hitType)
        cout << track_hitPattern.outermostMuonStationWithValidHits() << ' ';
        cout << track_hitPattern.outermostMuonStationWithBadHits() << ' ';
        cout << track_hitPattern.outermostMuonStationWithAnyHits() << ' ';
        cout << track_hitPattern.numberOfDTStationsWithRPhiView() << ' ';
        cout << track_hitPattern.numberOfDTStationsWithRZView() << ' ';
        cout << track_hitPattern.numberOfDTStationsWithBothViews() << ' ';
        cout << endl;
    }
}


void Validation::beginJob()
{
    ;
}

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

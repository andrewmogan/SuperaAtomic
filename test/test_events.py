
bbox_cfg = {
    "BBoxSize": "[ 740,  320,  530]",
    "VoxelSize": "[0.4,   0.4,  0.4]",
    "BBoxBottom": "[-370, -160,  400]",
}

label_cfg = {
    "LogLevel": "VERBOSE",

    "EnergyDepositThreshold":  "0",
    "UseSimEnergyDeposit":       "True",  # currently unused but required parameter
    "UseSimEnergyDepositPoints": "False", # ditto

}

def test_events():
    import supera

    driver = supera.Driver()
    driver.ConfigureBBoxAlgorithm("BBoxInteraction", bbox_cfg)
    driver.ConfigureLabelAlgorithm("LArTPCMLReco3D", label_cfg)

    for evnum, (evname, testev) in enumerate(supera.test.TestEvents().items()):
        driver.GenerateImageMeta(testev.input)
        driver.GenerateLabel(testev.input)

        same = True
        if not supera.test.VerifyEventMeta(driver.Meta(), testev.output_meta):
            same = False
            print("Metadata for test event '%s' disagrees with expectation." % evname)
            print("Expected metadata:")
            print(testev.output_meta.dump())
            print("Metadata received:")
            print(driver.Meta().dump())

        if not supera.test.VerifyEventLabels(driver.Label(), testev.output_labels):
            same = False
            print("Labels for test event '%s' disagree with expectation." % evname)
            print("Expected particle content:")
            for label in testev.output_labels.particles:
                print(label.dump())
            print("Received particle content:")
            for label in driver.Label().particles:
                print(label.dump())

        if not same:
            raise RuntimeError("Event #%d ('%s') failed test!" % (evnum, evname))


if __name__ == "__main__":
    test_events()

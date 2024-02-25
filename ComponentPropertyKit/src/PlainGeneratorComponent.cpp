#include "PlainGeneratorComponent.h"

namespace comp_prop_kit_lib {
    void PlainGeneratorComponent::setSavingChunk(bool needSaving) {
        mNeedSave = true;
    }

    double PlainGeneratorComponent::findPoint(int globalX, int globalY) {
        if (mNeedSave) {
            auto comp = [&](const Point& point) { return point.x == globalX & point.y == globalY; };
            auto iter = std::find_if(mSavedPoints.begin(), mSavedPoints.end(), comp);
            if (iter == mSavedPoints.end()) {
                mSavedPoints.push_back(Point{ globalX, globalY, mRandomizer.next(0.0, 1.0) });
                return mSavedPoints.rbegin()->value;
            } else
                return iter->value;
        } else return mRandomizer.next(0.0, 1.0);

    }
}

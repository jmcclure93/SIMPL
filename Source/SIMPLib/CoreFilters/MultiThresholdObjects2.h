/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#ifndef _multithresholdobjects2_h_
#define _multithresholdobjects2_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/Filtering/ComparisonInputsAdvanced.h"
#include "SIMPLib/Filtering/ComparisonSet.h"
#include "SIMPLib/Filtering/ComparisonValue.h"
#include "SIMPLib/SIMPLib.h"

/**
 * @brief The MultiThresholdObjects2 class. See [Filter documentation](@ref multithresholdobjects2) for details.
 */
class  SIMPLib_EXPORT MultiThresholdObjects2 : public AbstractFilter
{
    Q_OBJECT
    PYB11_CREATE_BINDINGS(MultiThresholdObjects2 SUPERCLASS AbstractFilter)
    PYB11_PROPERTY(QString DestinationArrayName READ getDestinationArrayName WRITE setDestinationArrayName)
    PYB11_PROPERTY(ComparisonInputsAdvanced SelectedThresholds READ getSelectedThresholds WRITE setSelectedThresholds)

  public:
    SIMPL_SHARED_POINTERS(MultiThresholdObjects2)
    SIMPL_FILTER_NEW_MACRO(MultiThresholdObjects2)
    SIMPL_TYPE_MACRO_SUPER_OVERRIDE(MultiThresholdObjects2, AbstractFilter)

    ~MultiThresholdObjects2() override;

    SIMPL_FILTER_PARAMETER(QString, DestinationArrayName)
    Q_PROPERTY(QString DestinationArrayName READ getDestinationArrayName WRITE setDestinationArrayName)

    SIMPL_FILTER_PARAMETER(ComparisonInputsAdvanced, SelectedThresholds)
    Q_PROPERTY(ComparisonInputsAdvanced SelectedThresholds READ getSelectedThresholds WRITE setSelectedThresholds)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    const QString getCompiledLibraryName() const override;

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
    */
    const QString getBrandingString() const override;

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    const QString getFilterVersion() const override;

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    const QString getGroupName() const override;

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    const QString getSubGroupName() const override;

    /**
     * @brief getUuid Return the unique identifier for this filter.
     * @return A QUuid object.
     */
    const QUuid getUuid() override;

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    const QString getHumanLabel() const override;

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    void setupFilterParameters() override;

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    void execute() override;

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    void preflight() override;

  signals:
    /**
     * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
     * be pushed from a user-facing control (such as a widget)
     * @param filter Filter instance pointer
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged Emitted when any Filter parameter is changed internally
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before calling dataCheck()
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after calling dataCheck()
     */
    void preflightExecuted();

  protected:
    MultiThresholdObjects2();
    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    void dataCheck();

    /**
     * @brief Initializes all the private instance variables.
     */
    void initialize();

    /**
    * @brief Creates and returns a DataArray<bool> for the given AttributeMatrix and the number of tuples
    */
    void createBoolArray(int64_t& numItems, BoolArrayType::Pointer& thresholdArrayPtr);
    
    /**
    * @brief Merges two DataArray<bool>s of a given size using a union operator AND / OR and inverts the second DataArray if requested
    * @param numItems Number of values in both DataArrays
    * @param currentArray DataArray<bool> to merge values into
    * @param unionOperator Union operator used to merge into currentArray
    * @param newArray DataArray<bool> of values to merge into the currentArray
    * @param inverse Should newArray have its boolean values flipped before being merged in
    */
    void insertThreshold(int64_t numItems, BoolArrayType::Pointer currentArray, int unionOperator, const BoolArrayType::Pointer newArray, bool inverse);
    
    /**
    * @brief Flips the boolean values for a DataArray<bool>
    * @param numItems Number of tuples in the DataArray
    * @param thresholdArray DataArray to invert
    */
    void invertThreshold(int64_t numItems, BoolArrayType::Pointer thresholdArray);

    /**
    * @brief Performs a check on a ComparisonSet and either merges the result into the DataArray passed in or replaces the DataArray
    * @param comparisonSet The set of comparisons used for setting the threshold
    * @param inputThreshold DataArray<bool> merged into or replaced after finding the ComparisonSet's threshould output
    * @param err Return any error code given
    * @param replaceInput Specifies whether or not the result gets merged into inputThreshold or replaces it
    * @param inverse Specifies whether or not the results need to be flipped before merging or replacing inputThreshold
    */
    void thresholdSet(ComparisonSet::Pointer comparisonSet, BoolArrayType::Pointer& inputThreshold, int32_t& err, bool replaceInput = false, bool inverse = false);
    
    /**
    * @brief Performs a check on a single ComparisonValue and either merges the result into the DataArray passed in or replaces the DataArray
    * @param comparisonValue The comparison operator and value used for caluculating the threshold
    * @param inputThreshold DataArray<bool> merged into or replaced after finding the ComparisonSet's threshould output
    * @param err Return any error code given
    * @param replaceInput Specifies whether or not the result gets merged into inputThreshold or replaces it
    * @param inverse Specifies whether or not the results need to be flipped before merging or replacing inputThreshold
    */
    void thresholdValue(ComparisonValue::Pointer comparisonValue, BoolArrayType::Pointer& inputThreshold, int32_t& err, bool replaceInput = false, bool inverse = false);


  private:
    DEFINE_DATAARRAY_VARIABLE(bool, Destination)

  public:
    MultiThresholdObjects2(const MultiThresholdObjects2&) = delete; // Copy Constructor Not Implemented
    MultiThresholdObjects2(MultiThresholdObjects2&&) = delete;      // Move Constructor
    MultiThresholdObjects2& operator=(const MultiThresholdObjects2&) = delete; // Copy Assignment Not Implemented
    MultiThresholdObjects2& operator=(MultiThresholdObjects2&&) = delete;      // Move Assignment
};

#endif /* _MultiThresholdObjects_H_ */

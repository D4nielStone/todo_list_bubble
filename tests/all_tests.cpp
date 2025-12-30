#include <gtest/gtest.h>
#include "bgui.hpp"

using namespace bgui;
TEST(ElementTest, GetID) {
    element a, b, c, d("TagTest");

    // 1. Id tests (different elements may have different ids)
    EXPECT_EQ(a.get_id(), "#0");
    EXPECT_EQ(b.get_id(), "#1");
    EXPECT_EQ(c.get_id(), "#2");
    EXPECT_EQ(d.get_id(), "TagTest#3");
}

TEST(ElementTest, requireSizeAndMode) {
    element elem;
    
    // 1. Reuqest Size Test (default mode is pixel)
    elem.require_size(150.f, 200.f);
    
    EXPECT_FLOAT_EQ(elem.required_size()[0], 150.f);
    EXPECT_FLOAT_EQ(elem.required_size()[1], 200.f);

    EXPECT_EQ(elem.get_required_mode()[0], mode::pixel);
    EXPECT_EQ(elem.get_required_mode()[1], mode::pixel);
    
    // 2. Test with percentual mode
    elem.require_width(mode::percent, 50.f);
    elem.require_height(mode::percent, 25.f);

    EXPECT_FLOAT_EQ(elem.required_size()[0], 50.f);
    EXPECT_FLOAT_EQ(elem.required_size()[1], 25.f);
    EXPECT_EQ(elem.get_required_mode()[0], mode::percent);
    EXPECT_EQ(elem.get_required_mode()[1], mode::percent);
}

TEST(ElementTest, FinalRectManipulation) {
    element elem;
    
    // 1. Manual final rect set
    elem.set_final_rect(10, 20, 100, 50);

    // 2. Verify getters
    EXPECT_EQ(elem.processed_x(), 10);
    EXPECT_EQ(elem.processed_y(), 20);
    EXPECT_EQ(elem.processed_width(), 100);
    EXPECT_EQ(elem.processed_height(), 50);

    EXPECT_EQ(elem.processed_position()[0], 10);
    EXPECT_EQ(elem.processed_size()[1], 50);
    EXPECT_EQ(elem.processed_rect()[3], 50); // height

    elem.set_position(5, 15);
    EXPECT_EQ(elem.processed_x(), 5);
    EXPECT_EQ(elem.processed_y(), 15);
    EXPECT_EQ(elem.processed_width(), 100);

    elem.set_final_size(80, 40);
    EXPECT_EQ(elem.processed_width(), 80);
    EXPECT_EQ(elem.processed_height(), 40);
    EXPECT_EQ(elem.processed_x(), 5);
}
const vec2i AVAILABLE_SIZE = {400, 300};

TEST(ElementTest, UpdateSizeCalculation) {
    element elem;

    // 1. Test pixel mode
    elem.require_size(100.f, 50.f);

    elem.process_required_size(AVAILABLE_SIZE); 
    
    EXPECT_EQ(elem.processed_width(), 100);
    EXPECT_EQ(elem.processed_height(), 50);

    // 2. Test percentual mode
    elem.require_width(mode::percent, 50.f);
    elem.require_height(mode::percent, 25.f);

    elem.process_required_size(AVAILABLE_SIZE);
    
    // 50% of 400 = 200
    EXPECT_EQ(elem.processed_width(), 200); 
    // 25% of 300 = 75
    EXPECT_EQ(elem.processed_height(), 75);

    // 3. Test match parent
    elem.require_width(mode::match_parent, 0.f);
    elem.require_height(mode::match_parent, 0.f);
    
    elem.process_required_size(AVAILABLE_SIZE);

    EXPECT_EQ(elem.processed_width(), 400); 
    EXPECT_EQ(elem.processed_height(), 300);

    // 4. Test percent and pixel
    elem.require_width(mode::percent, 10.f);
    elem.require_height(mode::pixel, 120.f);
    
    elem.process_required_size(AVAILABLE_SIZE);

    // 10% of 400 = 40
    EXPECT_EQ(elem.processed_width(), 40);
    EXPECT_EQ(elem.processed_height(), 120);

    // 5. Test padding and margin:
    // Paddings and Margins SHOULD NOT affect the content.
    elem.set_padding(10, 10, 10, 10); // L, T, R, B
    elem.set_margin(5, 5, 5, 5);     // L, T, R, B

    elem.require_size(50.f, 50.f); 
    elem.require_mode(mode::pixel, mode::pixel); 
    elem.process_required_size(AVAILABLE_SIZE);

    EXPECT_EQ(elem.processed_width(), 50);
    EXPECT_EQ(elem.processed_height(), 50);

    // 6. Test Stretched
    vec2i stretch_size = {150, 150};
    elem.require_size(1.f, 1.f);
    elem.require_mode(mode::stretch, mode::stretch);
    elem.process_required_size(stretch_size);
    
    EXPECT_EQ(elem.processed_width(), 150);
    EXPECT_EQ(elem.processed_height(), 150);
}

// Mock element class for testing
class mock_element : public element {
public:
    mock_element(int w, int h, mode w_mode = mode::pixel, mode h_mode = mode::pixel) {
        require_size(static_cast<float>(w), static_cast<float>(h));
        require_mode(w_mode, h_mode);
    }

    void on_update() override {}
};

class linear_test : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup common test fixtures
    }

    void TearDown() override {
        // Cleanup
    }
};

// Test: Constructor initializes correctly
TEST_F(linear_test, ConstructorVertical) {
    bgui::set_up();

    linear layout(orientation::vertical);
    EXPECT_FALSE(layout.is_visible());
}

TEST_F(linear_test, ConstructorHorizontal) {
    bgui::set_up();

    linear layout(orientation::horizontal);
    EXPECT_FALSE(layout.is_visible());
}

// Test: Empty layout
TEST_F(linear_test, EmptyLayoutContentSize) {
    bgui::set_up();

    linear layout(orientation::vertical);
    layout.set_padding(10, 20, 10, 20);
    
    EXPECT_FLOAT_EQ(layout.content_width(), 20.0f);  // left + right padding
    EXPECT_FLOAT_EQ(layout.content_height(), 40.0f); // top + bottom padding
}

// Test: Vertical layout with fixed size elements
TEST_F(linear_test, VerticalLayoutFixedSizes) {
    bgui::set_up();
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({200, 400});
    
    auto& elem1 = layout.add<mock_element>(100, 50);
    auto& elem2 = layout.add<mock_element>(100, 75);
    auto& elem3 = layout.add<mock_element>(100, 100);
    
    layout.on_update();
    
    // Check that elements are positioned vertically
    EXPECT_EQ(elem1.processed_y(), 0);
    EXPECT_EQ(elem2.processed_y(), 50);
    EXPECT_EQ(elem3.processed_y(), 125);
}

// Test: Horizontal layout with fixed size elements
TEST_F(linear_test, HorizontalLayoutFixedSizes) {
    bgui::set_up();
    linear layout(orientation::horizontal);
    layout.require_size(400, 200);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({400, 200});
    
    auto& elem1 = layout.add<mock_element>(50, 100);
    auto& elem2 = layout.add<mock_element>(75, 100);
    auto& elem3 = layout.add<mock_element>(100, 100);
    
    layout.on_update();
    
    // Check that elements are positioned horizontally
    EXPECT_EQ(elem1.processed_x(), 0);
    EXPECT_EQ(elem2.processed_x(), 50);
    EXPECT_EQ(elem3.processed_x(), 125);
}

// Test: Stretch mode in vertical layout
TEST_F(linear_test, VerticalLayoutWithStretch) {
    bgui::set_up();
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({200, 400});
    
    auto& elem1 = layout.add<mock_element>(100, 50, mode::pixel, mode::pixel);
    auto& elem2 = layout.add<mock_element>(100, 0, mode::pixel, mode::stretch);
    auto& elem3 = layout.add<mock_element>(100, 50, mode::pixel, mode::pixel);
    
    layout.on_update();
    
    // elem2 should stretch to fill remaining space: 400 - 50 - 50 = 300
    EXPECT_EQ(elem2.processed_height(), 300);
}

// Test: Multiple stretch elements share space equally
TEST_F(linear_test, MultipleStretchElements) {
    bgui::set_up();
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({200, 400});
    
    auto &elem1 = layout.add<mock_element>(100, 0, mode::pixel, mode::stretch);
    auto &elem2 = layout.add<mock_element>(100, 0, mode::pixel, mode::stretch);
    
    layout.on_update();
    
    // Each should get half: 400 / 2 = 200
    EXPECT_EQ(elem1.processed_height(), 200);
    EXPECT_EQ(elem2.processed_height(), 200);
}

// Test: Match parent mode
TEST_F(linear_test, MatchParentCrossAxis) {
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({200, 400});
    
    
    auto& elem1 = layout.add<mock_element>(0, 100, mode::match_parent, mode::pixel);
    layout.on_update();
    
    // Width should match parent
    EXPECT_EQ(elem1.processed_width(), 200);
}

// Test: Padding affects layout
TEST_F(linear_test, PaddingAffectsLayout) {
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.set_padding(10, 20, 10, 20); // left, top, right, bottom
    layout.process_required_size({200, 400});
    
    auto& elem1 = layout.add<mock_element>(100, 50);
    layout.on_update();
    
    // Element should be positioned after top padding
    EXPECT_EQ(elem1.processed_y(), 20);
    EXPECT_EQ(elem1.processed_x(), 10);
}

// Test: Margins affect spacing
TEST_F(linear_test, MarginsAffectSpacing) {
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.process_required_size({200, 400});
        
    auto& elem1 = layout.add<mock_element>(100, 50);
    auto& elem2 = layout.add<mock_element>(100, 50);
    elem1.set_margin(0, 10, 0, 10); // 10px margin top and bottom
    layout.on_update();
    
    // elem2 should be after elem1 height + margins: 10 + 50 + 10 = 70
    EXPECT_EQ(elem2.processed_y(), 70);
}

// Test: Start alignment
TEST_F(linear_test, AlignmentStart) {
    bgui::set_up();
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.set_alignment(alignment::start);
    layout.process_required_size({200, 400});
    
    auto& elem1 = layout.add<mock_element>(100, 50);
    layout.on_update();
    
    EXPECT_EQ(elem1.processed_y(), 0);
}

// Test: Center alignment
TEST_F(linear_test, AlignmentCenter) {
    bgui::set_up();
    linear layout(orientation::vertical);
    layout.require_size(200, 400);
    layout.require_mode(mode::pixel, mode::pixel);
    layout.set_alignment(alignment::center);
    layout.process_required_size({200, 400});
    
    auto& elem1 = layout.add<mock_element>(100, 100);
    
    layout.on_update();
    
    // Element should be centered: (400 - 100) / 2 = 150
    EXPECT_EQ(elem1.processed_y(), 150);
}
/*
// Test: End alignment
TEST_F(linear_test, AlignmentEnd) {
    linear layout(orientation::vertical);
    layout.require_size({200, 400});
    layout.require_mode({mode::pixel, mode::pixel});
    layout.set_alignment(alignment::end);
    layout.process_required_size({200, 400});
    
    auto elem1 = std::make_shared<mock_element>(100, 100);
    
    layout.add(elem1);
    layout.on_update();
    
    // Element should be at end: 400 - 100 = 300
    EXPECT_EQ(elem1->processed_y(), 300);
}

// Test: Cross-axis center alignment
TEST_F(linear_test, CrossAxisCenterAlignment) {
    linear layout(orientation::vertical);
    layout.require_size({200, 400});
    layout.require_mode({mode::pixel, mode::pixel});
    layout.set_cross_alignment(alignment::center);
    layout.process_required_size({200, 400});
    
    auto elem1 = std::make_shared<mock_element>(100, 50);
    
    layout.add(elem1);
    layout.on_update();
    
    // Element should be centered horizontally: (200 - 100) / 2 = 50
    EXPECT_EQ(elem1->processed_x(), 50);
}

// Test: Content width calculation for vertical layout
TEST_F(linear_test, ContentWidthVertical) {
    linear layout(orientation::vertical);
    layout.set_padding(5, 10, 5, 10);
    
    auto elem1 = std::make_shared<mock_element>(100, 50);
    auto elem2 = std::make_shared<mock_element>(150, 50);
    auto elem3 = std::make_shared<mock_element>(80, 50);
    
    elem1->process_required_size({100, 50});
    elem2->process_required_size({150, 50});
    elem3->process_required_size({80, 50});
    
    layout.add(elem1);
    layout.add(elem2);
    layout.add(elem3);
    
    // Width should be max element width + padding: 150 + 5 + 5 = 160
    EXPECT_FLOAT_EQ(layout.content_width(), 160.0f);
}

// Test: Content height calculation for horizontal layout
TEST_F(linear_test, ContentHeightHorizontal) {
    linear layout(orientation::horizontal);
    layout.set_padding(5, 10, 5, 10);
    
    auto elem1 = std::make_shared<mock_element>(50, 100);
    auto elem2 = std::make_shared<mock_element>(50, 150);
    auto elem3 = std::make_shared<mock_element>(50, 80);
    
    elem1->process_required_size({50, 100});
    elem2->process_required_size({50, 150});
    elem3->process_required_size({50, 80});
    
    layout.add(elem1);
    layout.add(elem2);
    layout.add(elem3);
    
    // Height should be max element height + padding: 150 + 10 + 10 = 170
    EXPECT_FLOAT_EQ(layout.content_height(), 170.0f);
}

// Test: Percent mode
TEST_F(linear_test, PercentMode) {
    linear layout(orientation::vertical);
    layout.require_size({200, 400});
    layout.require_mode({mode::pixel, mode::pixel});
    layout.process_required_size({200, 400});
    
    auto elem1 = std::make_shared<mock_element>(0, 0, mode::percent, mode::percent);
    elem1->require_size(50.f, 25.f); // 50% width, 25% height
    
    layout.add(elem1);
    layout.on_update();
    
    EXPECT_EQ(elem1->processed_width(), 100);  // 50% of 200
    EXPECT_EQ(elem1->processed_height(), 100); // 25% of 400
}

// Test: Negative space handling
TEST_F(linear_test, NegativeSpaceHandling) {
    linear layout(orientation::vertical);
    layout.require_size({200, 100});
    layout.require_mode({mode::pixel, mode::pixel});
    layout.process_required_size({200, 100});
    
    // Add elements that exceed available space
    auto elem1 = std::make_shared<mock_element>(100, 80);
    auto elem2 = std::make_shared<mock_element>(100, 80);
    
    layout.add(elem1);
    layout.add(elem2);
    
    // Should not crash and handle gracefully
    EXPECT_NO_THROW(layout.on_update());
}*/
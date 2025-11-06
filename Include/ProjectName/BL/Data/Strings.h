#pragma once

#pragma once
#include <string>

namespace Messerli::Data
{

namespace Menu
{
static const std::string MenuHeader = "\n====== ShapeDrawings ======\n";
static const std::string MenuQuestionMode = "\nSelect Mode:\n";
static const std::string MenuOptionPolyline = "1. Polyline";
static const std::string MenuOptionRectangle = "2. Rectangle";
static const std::string MenuOptionCircle = "3. Circle";
static const std::string MenuOptionEllipse = "4. Ellipse";
static const std::string MenuOptionLine = "5. Line";
static const std::string MenuOptionPolygon = "6. Polygon";

static inline const std::string MenuOptionExit = "0. Exit Application";

}

namespace Polyline
{
static const std::string PolylineHeader = "\n====== Polyline Mode ======\n";
static const std::string PolylineDef = "A polyline is defined by multiple points connected by straight lines.\n";
static const std::string PolylineInput = "Enter the number of lines for the polyline (minimum 2): ";
static const std::string PolylineReturnMessage = "A polyline must have at least 2 lines. Returning to main menu.\n";
static const std::string PolylineCreatet = "\nYou created the following polyline:\n";
static const std::string PolylineTotalLength = "Total Length: ";

}

namespace UniversalMenu
{
static const std::string Enter = "Enter the Coordinates for the anchor point:\n";
static const std::string EnterEndpoint = "Enter the coordinates for point ";

}

namespace Line
{
static const std::string LineHeader = "\n====== Line Mode ======\n";
static const std::string LineDef = "A line is defined by two points: an anchor point and an endpoint.\n";

}

namespace Polygon
{
static const std::string PolygonHeader = "\n===== Polygon Mode =====\n ";
static const std::string PolygonDefine =
    "A polygon is a closed shape defined by multiple points connected by straight lines.\n";
static const std::string PolygonEdges = "Enter the number of edges for the polygon (minimum 3): ";
static const std::string PolygonReturnMessage = "A polygon must have at least 3 edges. Returning to main menu.\n";
static const std::string PolygonSecondEdge = "Enter the coordinates for the second point:\n";
}

namespace Rectangle
{
static const std::string RectangleHeader = "\n===== Rectangle Mode =====\n";
static const std::string RectangleDefinition = "A Rectangle has 4 Lines, where 4 are parallel. ";
static const std::string RectangleInput = "Please enter the width and height of your rectangle";
static const std::string RectangleAnchorPos = "Please Enter the X and Y of your Anchor";

}

namespace Ellipse
{

static const std::string EllipseHeader = "\n====== Ellipse Mode ======\n";
static const std::string EllipseDefinition = "An Ellipse is a Circle with two different half-radient. ";
static const std::string EllipseMiddlePoint = "Please enter the X and Y of your middle point: ";
static const std::string EllipseRadient = "Please enter the two radient of your Ellipse";

}

namespace Circle
{

static const std::string CircleHeader = "\n====== Circle Mode =======\n";
static const std::string CircleDefinition = "A Circle is a Line arount a Middlepoint with a static radient.\n";
static const std::string CircleRadient = "Please Entere your radient.\n";
}
}

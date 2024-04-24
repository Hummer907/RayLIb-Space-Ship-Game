

bool IsPointOnLineSegment(const Vector2& p, const Vector2& q, const Vector2& r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
    {
        return true;
    }
    return false;
}


bool CheckLinesIntersect(const Vector2& p1, const Vector2& q1, const Vector2& p2, const Vector2& q2)
{
    // Calculate the orientation of three points (p, q, r)
    // Returns 0 if they are collinear, 1 if clockwise, and 2 if counterclockwise
    auto CalculateOrientation = [](const Vector2& p, const Vector2& q, const Vector2& r) {
        float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;  // Collinear
        return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
    };

    // Find the four orientations needed for general and special cases
    int o1 = CalculateOrientation(p1, q1, p2);
    int o2 = CalculateOrientation(p1, q1, q2);
    int o3 = CalculateOrientation(p2, q2, p1);
    int o4 = CalculateOrientation(p2, q2, q1);

    // General case: If the orientations of p1, q1, p2, and q2 are all different, the lines intersect
    if (o1 != o2 && o3 != o4)
        return true;

    // Special cases: Collinear points
    if (o1 == 0 && IsPointOnLineSegment(p1, p2, q1)) return true;
    if (o2 == 0 && IsPointOnLineSegment(p1, q2, q1)) return true;
    if (o3 == 0 && IsPointOnLineSegment(p2, p1, q2)) return true;
    if (o4 == 0 && IsPointOnLineSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall into any of the above cases
}

bool IsPointInsideTriangle(const Vector2& p, const Vector2& v1, const Vector2& v2, const Vector2& v3)
{
    // Calculate the barycentric coordinates of point p with respect to triangle v1v2v3
    float u = ((v2.y - v3.y) * (p.x - v3.x) + (v3.x - v2.x) * (p.y - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
    float v = ((v3.y - v1.y) * (p.x - v3.x) + (v1.x - v3.x) * (p.y - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));

    // Check if the point is inside the triangle using barycentric coordinates
    if (u >= 0 && v >= 0 && (u + v) <= 1)
        return true;

    return false;
}




bool CheckTriangleRectangleCollision(const Vector2& v1, const Vector2& v2, const Vector2& v3, const Vector2& mTopLeft, const Vector2& mTopRight, const Vector2& mBottomLeft, const Vector2& mBottomRight)
{
    // Check if any of the triangle's edges intersect with the rectangle
    if (CheckLinesIntersect(v1, v2, mTopLeft, mTopRight) ||
        CheckLinesIntersect(v2, v3, mTopLeft, mTopRight) ||
        CheckLinesIntersect(v3, v1, mTopLeft, mTopRight) ||
        CheckLinesIntersect(v1, v2, mTopLeft, mBottomLeft) ||
        CheckLinesIntersect(v2, v3, mTopLeft, mBottomLeft) ||
        CheckLinesIntersect(v3, v1, mTopLeft, mBottomLeft) ||
        CheckLinesIntersect(v1, v2, mBottomRight, mTopRight) ||
        CheckLinesIntersect(v2, v3, mBottomRight, mTopRight) ||
        CheckLinesIntersect(v3, v1, mBottomRight, mTopRight) ||
        CheckLinesIntersect(v1, v2, mBottomRight, mBottomLeft) ||
        CheckLinesIntersect(v2, v3, mBottomRight, mBottomLeft) ||
        CheckLinesIntersect(v3, v1, mBottomRight, mBottomLeft))
    {
        return true;
    }

    // Check if the rectangle is completely inside the triangle
    if (IsPointInsideTriangle(mTopLeft, v1, v2, v3) &&
        IsPointInsideTriangle(mTopRight, v1, v2, v3) &&
        IsPointInsideTriangle(mBottomLeft, v1, v2, v3) &&
        IsPointInsideTriangle(mBottomRight, v1, v2, v3))
    {
        return true;
    }

    return false;
}


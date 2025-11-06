# DrawSomeShapes


### 📘 Zweck

Das Projekt _Shapes  ist eine interaktive C++-Anwendung, die es ermöglicht, verschiedene geometrische Formen (z. B. Linie, Rechteck, Kreis, Ellipse, Polygon, Polyline) anzulegen, zu verwalten und auf der Konsole bzw. in einer grafischen Oberfläche (über `POINT`-Strukturen und `WindCanvas.cpp`) zu zeichnen.  
Das Projekt ist didaktisch orientiert und dient zur **Objektorientierten Modellierung und Polymorphie mit Zeigern** – **ohne STL-Container oder Smartpointer**.

---

## 🧠 **Architektur und Designprinzipien**

### 🔹 **Basisklasse `Shapes`**

Alle Formen erben von dieser abstrakten Basisklasse.

```cpp
class Shapes {
protected:
    Point m_Anchor;  // Ausgangspunkt (Referenzpunkt) der Form
public:
    Shapes();
    explicit Shapes(const Point& anchor);
    virtual ~Shapes() = default;

    virtual std::string ToString() const;
    virtual const Point& GetAnchor() const;
    virtual void ExportDevicePoints(POINT* points, int& count) const = 0;
    virtual void Scale(double factor);
    virtual Shapes* Clone() const;
};
```

#### ✳️ Hauptaufgaben:

- Definiert die gemeinsame Schnittstelle für alle geometrischen Objekte.
    
- Stellt die gemeinsame Position `m_Anchor` bereit.
    
- Enthält virtuelle Funktionen für Darstellung (`ToString`), Transformation (`Move`, `Scale`), und Ausgabe (`ExportDevicePoints`).
    
- `ExportDevicePoints` ist **pure virtual**, d. h. jede Unterklasse muss ihre eigene Zeichenlogik implementieren.
    

#### 💡 Designprinzip:

→ **Polymorphie:** Alle abgeleiteten Formen können über `Shapes*` verwaltet werden.  
→ **Erweiterbarkeit:** Neue Formen können hinzugefügt werden, ohne bestehende Logik zu ändern.

---

### 🔹 **Hilfsklasse `Point`**

Ein einfacher 2D-Punkt mit x- und y-Koordinate, Operatorüberladungen und Hilfsfunktionen.

```cpp
class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0);
    Point operator+(const Point&) const;
    Point operator-(const Point&) const;
    Point& operator*=(double factor);
    static double Distance(const Point&, const Point&);
};
```

#### ✳️ Funktionen:

- Rechenoperationen (Addition, Subtraktion, Skalierung)
    
- Distanzberechnung
    
- Wird in allen Shapes als Basisdatentyp verwendet.
    

---

### 🔹 **Abgeleitete Klassen**

#### **1. `Ellipse`**

Erbt von `Shapes`  
→ Modelliert eine Ellipse über zwei Halbachsen (A und B).

```cpp
class Ellipse : public Shapes {
    double m_halfAxleA;
    double m_halfAxleB;
public:
    Ellipse();
    Ellipse(const Point& anchor, double halfAxleA, double halfAxleB);
    void Scale(double factor) override;
    void ExportDevicePoints(POINT* points, int& count) const override;
    std::string ToString() const override;
    double GetCircumference() const;
};
```

#### ✳️ Verhalten:

- `Scale()` multipliziert beide Halbachsen.
    
- `ExportDevicePoints()` berechnet 36 gleichmäßig verteilte Punkte auf der Ellipse.
    
- `ToString()` gibt Koordinaten und Achsenmaße aus.
    

---

#### **2. `Circle`**

Erbt von `Ellipse`, spezifiziert jedoch gleiche Halbachsen (A = B = Radius).

```cpp
class Circle : public Ellipse {
public:
    Circle();
    Circle(const Point& center, double radius);
    ~Circle() override;
    double GetRadius() const;
    void SetRadius(double radius);
    void ExportDevicePoints(POINT* points, int& count) const override;
};
```

#### ✳️ Verhalten:

- Einfacher Spezialfall der Ellipse.
    
- Exportiert 64 Punkte für die Kreislinie.
    
- Nutzt `GetHalfAxleA()` aus `Ellipse` als Radius.
    

---

#### **3. `Rectangle`**

Modelliert ein Rechteck über Breite, Höhe und Ankerpunkt.

```cpp
class Rectangle : public Shapes {
    double m_width;
    double m_height;
public:
    Rectangle();
    Rectangle(const Point& anchor, double width, double height);
    void ExportDevicePoints(POINT* points, int& count) const override;
    std::string ToString() const override;
};
```

#### ✳️ Verhalten:

- Zeichnet vier Eckpunkte.
    
- Gibt in `ToString()` Breite, Höhe und Anker aus.
    

---

#### **4. `Line`**

Einfaches Liniensegment zwischen zwei Punkten.

```cpp
class Line : public Shapes {
    Point m_End;
public:
    Line(const Point& start, const Point& end);
    void ExportDevicePoints(POINT* points, int& count) const override;
};
```

#### ✳️ Verhalten:

- Repräsentiert einen Vektor von `m_Anchor` zu `m_End`.
    
- `ExportDevicePoints` gibt zwei `POINT`s zurück.
    

---

#### **5. `Polygon`**

Ein geschlossener Linienzug (mehrere Punkte verbunden, letzter Punkt = erster Punkt).

```cpp
class Polygon : public Shapes {
    Point* m_arr;
    int m_edges;
public:
    Polygon();
    Polygon(const Point& anchor, Point* arr, int edges);
    ~Polygon();
    void ExportDevicePoints(POINT* points, int& count) const override;
    std::string ToString() const override;
};
```

#### ✳️ Verhalten:

- Dynamische Speicherung der Ecken (`Point* m_arr`).
    
- Automatisch geschlossene Figur (letzter Punkt = erster Punkt).
    
- Gibt Eckenanzahl und Umfang aus.
    

---

#### **6. `Polyline`**

Ein offener Linienzug, d. h. eine Reihe verbundener Punkte ohne Schließung.

```cpp
class Polyline : public Shapes {
    Point* m_arr;
    int m_amountLines;
public:
    Polyline();
    Polyline(const Point& pointA, const Point& pointB);
    Polyline(Point* arr, int amountLines);
    ~Polyline();
    Polyline& operator+=(const Point& point);
    Polyline& operator+=(const Polyline& other);
    void Scale(double factor) override;
    double GetTotalLength() const;
    void ExportDevicePoints(POINT* points, int& count) const override;
};
```

#### ✳️ Verhalten:

- Punkte werden relativ zum Anker gespeichert.
    
- `operator+=` fügt Punkte oder andere Polylines hinzu.
    
- `Scale()` multipliziert alle Koordinaten mit einem Faktor.
    
- `GetTotalLength()` berechnet die Länge des gesamten Linienzuges.
    
- Dynamische Speicherverwaltung (`new[]` / `delete[]`) → ohne STL.
    

---

## ⚙️ **Programmlogik (Main Loop)**

- Hauptmenü mit Auswahl:
    
    ```
    1. Polyline
    2. Rectangle
    3. Circle
    4. Ellipse
    5. Line
    6. Polygon
    7. Multiple Shapes
    8. Exit Application
    ```
    
- Benutzer kann Formparameter eingeben (Koordinaten, Radien etc.).
    
- Jede erstellte Form wird in einer Sammlung (wahrscheinlich `ShapePtrList`) gespeichert.
    
- Bei Auswahl `7` können mehrere Shapes kombiniert werden.
    
- Am Ende werden alle Formen mit `ExportDevicePoints()` gezeichnet.
    
- Programm endet mit **CRT-Memory-Leak-Check**, der undestroyte Objekte meldet.
    

---

## 🧩 **Wichtige technische Punkte**

|Thema|Status|Bemerkung|
|:--|:--|:--|
|**Virtuelle Destruktoren**|✅ vorhanden|korrekt für Polymorphie|
|**Deep Copy (Polyline, Polygon)**|✅ implementiert|Kopierkonstruktor vorhanden|
|**Dynamic Memory**|⚠️ manuell (`new[]`, `delete[]`)|korrekt, aber anfällig für Leaks|
|**Container / Smartpointer**|🚫 verboten|daher nur manuelle Verwaltung|
|**Zeichenlogik (`ExportDevicePoints`)**|✅ korrekt|nutzt trigonometrische Berechnung|
|**Leak Detection**|✅ aktiv|`_CrtDumpMemoryLeaks()` am Ende|
|**Fehlerquellen**|🔸 fehlende `delete` in ShapePtrList|führt zu Leaks beim Programmende|
|**Style / Architektur**|🧠 lehrbuchartig|Demonstriert OOP, Polymorphie, Vererbung, virtuelle Methoden|

---

## 🧮 **Mathematische Grundlagen**

|Form|Formel / Methode|
|:--|:--|
|**Ellipse**|Punkte: `(x + a·cosθ, y + b·sinθ)`|
|**Kreis**|Spezialisierung mit `a = b = r`|
|**Polyline**|Länge = Σ Distanz(Pᵢ, Pᵢ₊₁)|
|**Polygon**|Umfang = Summe der Kantenlängen|
|**Rectangle**|4 Eckpunkte aus `Anchor`, `width`, `height`|

---

## 🧾 **Gesamtbewertung**

|Kriterium|Bewertung|
|:--|:--|
|**Architekturqualität**|★★★★☆ (klar, modular, sauber getrennt)|
|**Codequalität**|★★★★☆ (lesbar, konsistent, robust)|
|**Speicherverwaltung**|★★★☆☆ (korrekt, aber manuell und riskant)|
|**Polymorphieeinsatz**|★★★★★ (ideal umgesetzt)|
|**Didaktischer Wert**|★★★★★ (perfekt für Ausbildung)|

---

## 💬 **Zusammenfassung in einem Satz**

> _„Shapes “ ist ein objektorientiertes C++-Projekt, das polymorphe Geometrieobjekte modelliert, dynamisch verwaltet und grafisch exportiert — technisch solide, methodisch korrekt, lehrreich in Konstruktion, Destruktion und Vererbung, jedoch ohne moderne Speicherabstraktionen wie STL oder Smartpointer._

---

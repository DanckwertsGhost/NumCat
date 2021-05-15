VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTestImplement"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Implements TESTMODELINTERFACE1Lib.TITestInter


Private bInProg As Boolean
Private m_sOpen As String
Private m_iNumCols As Long
Private m_iNumRows As Long
Private m_App As Excel.Application
Private m_wks As Excel.Worksheet



Private Sub Class_Initialize()
    bInProg = False
    m_iNumCols = 0
    Set m_wks = Nothing
    Set m_App = Excel.Application
End Sub

Public Function TITestInter_AddOne(ByVal iValIn As Integer) As Integer
    TITestInter_AddOne = iValIn + 1


End Function

Private Function TITestInter_EndOutput() As Boolean
    bInProg = False
    m_iNumCols = 0
    m_App.Calculate
    With m_App
        .Calculation = xlCalculationAutomatic
        .MaxChange = 0.001
    End With
    m_wks.Visible = xlSheetVisible
    TITestInter_EndOutput = True

End Function

Private Sub TITestInter_HeaderRow(pphr() As String)
    Dim i As Long
    If Not IsNull(m_wks) Then
        For i = 1 To m_iNumCols
            m_wks.Cells(1, i).Value = pphr(i)
        Next i
        Else
        Debug.Print "<Error> Sheet not defined when Header Row called"
        End If
        
End Sub

Private Property Get TITestInter_MaxCols() As Double
    TITestInter_MaxCols = 100
End Property

Private Property Get TITestInter_MaxRows() As Double
    TITestInter_MaxRows = 100
End Property


Private Function TITestInter_PrepareOutput(ByVal iNumCols As Long, ByVal iNumRows As Long, ByVal bName As String) As Boolean
    
    Dim shts As Sheets
    Dim wks As Worksheet
    bInProg = True
    m_sOpen = bName
    m_iNumCols = iNumCols
    m_iNumRows = iNumRows
    With m_App
        .Calculation = xlManual
        .MaxChange = 0.001
    End With
    
    Set shts = m_App.Worksheets
    
    If Not IsASheet(shts, bName) Then
           Set m_wks = shts.Add
           m_wks.Name = bName
           Else
           Set m_wks = shts(bName)
           End If
    m_wks.Visible = xlSheetHidden
    TITestInter_PrepareOutput = True
     
End Function

Private Sub TITestInter_Row(ByVal iRow As Long, dRow() As Double)
    Const iOffset As Long = 1
    
    If Not IsNull(m_wks) Then
        For i = 1 To m_iNumCols
            m_wks.Cells(iOffset + iRow, i).Value = dRow(i)
        Next i
        Else
        Debug.Print "<Error> Sheet not defined when Header Row called"
        End If
     
End Sub

Public Function IsASheet(ByRef shts As Excel.Sheets, ByRef sName As String) As Boolean
    
    Dim iCount As Long
    Dim bFound As Boolean
    
    iCount = 1
    bFound = False
        
    Do While (Not bFound) And (iCount <= shts.Count)
        If shts(iCount).Name = sName Then
                bFound = True
                Else
                iCount = iCount + 1
                End If
    Loop

    IsASheet = bFound
    
End Function

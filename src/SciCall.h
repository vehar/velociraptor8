/*
Inline wrappers for Scintilla API calls, arranged in the order and grouping
in which they appear in the Scintilla documentation.

The use of these inline wrapper functions with declared types will ensure
that we get the benefit of the compiler's type checking.
*/

extern HANDLE g_hScintilla;

inline void InitScintillaHandle(HWND hwnd) {
    g_hScintilla = (HANDLE)SendMessageW(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
}

class ScintillaWin;

// LRESULT WINAPI Scintilla_DirectFunction(HANDLE, UINT, WPARAM, LPARAM);
extern "C" sptr_t __stdcall Scintilla_DirectFunction(ScintillaWin *, UINT, uptr_t, sptr_t);
#define SciCall(m, w, l) Scintilla_DirectFunction((ScintillaWin *)g_hScintilla, m, w, l)

//  DeclareSciCall[RV][0-2] Macros
//
//  R: With an explicit return type
//  V: No return type defined ("void"); defaults to SendMessage's LRESULT
//  0-2: Number of parameters to define
#define DeclareSciCallR0(fn, msg, ret)                                                             \
                                                                                                   \
    __forceinline ret SciCall_##fn() { return ((ret)SciCall(SCI_##msg, 0, 0)); }
#define DeclareSciCallR1(fn, msg, ret, type1, var1)                                                \
                                                                                                   \
    __forceinline ret SciCall_##fn(type1 var1) {                                                   \
        return ((ret)SciCall(SCI_##msg, (WPARAM)(var1), 0));                                       \
    }
#define DeclareSciCallR2(fn, msg, ret, type1, var1, type2, var2)                                   \
                                                                                                   \
    __forceinline ret SciCall_##fn(type1 var1, type2 var2) {                                       \
        return ((ret)SciCall(SCI_##msg, (WPARAM)(var1), (LPARAM)(var2)));                          \
    }
#define DeclareSciCallV0(fn, msg)                                                                  \
                                                                                                   \
    __forceinline LRESULT SciCall_##fn() { return (SciCall(SCI_##msg, 0, 0)); }
#define DeclareSciCallV1(fn, msg, type1, var1)                                                     \
                                                                                                   \
    __forceinline LRESULT SciCall_##fn(type1 var1) {                                               \
        return (SciCall(SCI_##msg, (WPARAM)(var1), 0));                                            \
    }
#define DeclareSciCallV2(fn, msg, type1, var1, type2, var2)                                        \
                                                                                                   \
    __forceinline LRESULT SciCall_##fn(type1 var1, type2 var2) {                                   \
        return (SciCall(SCI_##msg, (WPARAM)(var1), (LPARAM)(var2)));                               \
    }

//=============================================================================
//
//  Selection and information
//
//
DeclareSciCallR0(GetLineCount, GETLINECOUNT, int);
DeclareSciCallV2(SetSel, SETSEL, int, anchorPos, int, currentPos);
DeclareSciCallV1(GotoPos, GOTOPOS, int, position);
DeclareSciCallV1(GotoLine, GOTOLINE, int, line);
DeclareSciCallR0(GetCurrentPos, GETCURRENTPOS, int);
DeclareSciCallR1(LineFromPosition, LINEFROMPOSITION, int, int, position);

//=============================================================================
//
//  Scrolling and automatic scrolling
//
//
DeclareSciCallV0(ScrollCaret, SCROLLCARET);
DeclareSciCallV2(SetXCaretPolicy, SETXCARETPOLICY, int, caretPolicy, int, caretSlop);
DeclareSciCallV2(SetYCaretPolicy, SETYCARETPOLICY, int, caretPolicy, int, caretSlop);

//=============================================================================
//
//  Style definition
//
//
DeclareSciCallR1(StyleGetFore, STYLEGETFORE, COLORREF, int, styleNumber);
DeclareSciCallR1(StyleGetBack, STYLEGETBACK, COLORREF, int, styleNumber);

//=============================================================================
//
//  Margins
//
//
DeclareSciCallV2(SetMarginType, SETMARGINTYPEN, int, margin, int, type);
DeclareSciCallV2(SetMarginWidth, SETMARGINWIDTHN, int, margin, int, pixelWidth);
DeclareSciCallV2(SetMarginMask, SETMARGINMASKN, int, margin, int, mask);
DeclareSciCallV2(SetMarginSensitive, SETMARGINSENSITIVEN, int, margin, BOOL, sensitive);
DeclareSciCallV2(SetFoldMarginColour, SETFOLDMARGINCOLOUR, BOOL, useSetting, COLORREF, colour);
DeclareSciCallV2(SetFoldMarginHiColour, SETFOLDMARGINHICOLOUR, BOOL, useSetting, COLORREF, colour);

//=============================================================================
//
//  Markers
//
//
DeclareSciCallV2(MarkerDefine, MARKERDEFINE, int, markerNumber, int, markerSymbols);
DeclareSciCallV2(MarkerSetFore, MARKERSETFORE, int, markerNumber, COLORREF, colour);
DeclareSciCallV2(MarkerSetBack, MARKERSETBACK, int, markerNumber, COLORREF, colour);

//=============================================================================
//
//  Folding
//
//
DeclareSciCallR1(GetLineVisible, GETLINEVISIBLE, BOOL, int, line);
DeclareSciCallR1(GetFoldLevel, GETFOLDLEVEL, int, int, line);
DeclareSciCallV1(SetFoldFlags, SETFOLDFLAGS, int, flags);
DeclareSciCallR1(GetFoldParent, GETFOLDPARENT, int, int, line);
DeclareSciCallR1(GetFoldExpanded, GETFOLDEXPANDED, int, int, line);
DeclareSciCallV1(ToggleFold, TOGGLEFOLD, int, line);
DeclareSciCallV1(EnsureVisible, ENSUREVISIBLE, int, line);

//=============================================================================
//
//  Lexer
//
//
DeclareSciCallV2(SetProperty, SETPROPERTY, const char *, key, const char *, value);

inline ScintillaWin *GetSciDirectPtr(HWND hwnd) {
    return (ScintillaWin *)SendMessageW(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
}

template <UINT msg> inline void SciRetCall(HWND hwnd) {
    ScintillaWin *w = GetSciDirectPtr(hwnd);
    Scintilla_DirectFunction(w, msg, 0, 0);
}

template <UINT msg, typename TRET> inline TRET SciRetCall(HWND hwnd) {
    ScintillaWin *w = GetSciDirectPtr(hwnd);
    return (TRET)Scintilla_DirectFunction(w, msg, 0, 0);
}

template <UINT msg, typename T1> void SciNoRetCall(HWND hwnd, T1 v1) {
    ScintillaWin *w = GetSciDirectPtr(hwnd);
    Scintilla_DirectFunction(w, msg, (WPARAM)v1, 0);
}

template <UINT msg, typename T1, typename T2> void SciNoRetCall(HWND hwnd, T1 v1, T2 v2) {
    ScintillaWin *w = GetSciDirectPtr(hwnd);
    Scintilla_DirectFunction(w, msg, (WPARAM)v1, (LPARAM)v2);
}

inline void SetXCaretPolicy(HWND w, int policy, int slop) {
    SciNoRetCall<SCI_SETXCARETPOLICY, int, int>(w, policy, slop);
}

inline void SetYCaretPolicy(HWND w, int policy, int slop) {
    SciNoRetCall<SCI_SETYCARETPOLICY, int, int>(w, policy, slop);
}

inline void SetSel(HWND w, int anchorPos, int currPos) {
    SciNoRetCall<SCI_SETSEL, int, int>(w, anchorPos, currPos);
}

inline int SciGetLineCount(HWND hwnd) { return SciRetCall<SCI_GETLINECOUNT, int>(hwnd); }

inline void SciSetHScrollBar(HWND hwnd, bool visible) {
    SciNoRetCall<SCI_SETHSCROLLBAR, bool>(hwnd, visible);
}

inline bool SciGetHScrollBar(HWND hwnd) { return SciRetCall<SCI_GETHSCROLLBAR, bool>(hwnd); }

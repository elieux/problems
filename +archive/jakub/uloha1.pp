{$define sDontSpeak}
{$undef sDebug}
{$mode objfpc}
Program Uloha1;
{
  Jednoduchy sklad:
  Bude to vyrobene tak, ze ze standardniho vstupu budou cteny radky
  jako prikazy:

    POLOZKA id [nazev] : je-li zadan nazev, priradi se id (neni-li id
                         definovano, vytvori se); neni-li zadan nazev,
                         id se smaze
    PRIDEJ id :          prida 1 k poctu id
    ODEBER id :          odebere 1 z poctu id
    POCET id :           zjisti pocet id
    NAZEV id :           vrati nazev id
    NAJDI nazev :        vrati id polozek, ktere maji v nazvu nazev
    KONEC :              ukonci program
}

{$ifdef sDebug}
Uses SysUtils, Crt;
{$else}
Uses SysUtils;
{$endif}
Type
  CommandCount = 0..8;
  MessageCount = 0..3;
  ErrorCount = 0..6;
  Command = Record
    No : CommandCount;
    Str : String;
  End;
  IDType = String;
  NameType = String;
  CountType = LongInt;
  ItemType = Record
    ID : IDType;
    Name : NameType;
    Count : CountType;
  End;
  PItemType = ^ItemType;
  StoreType = Array[0..255] Of ItemType;
Const
  Cms : Array[CommandCount] Of Command =
    ((No : 0; Str : ''),
     (No : 1; Str : ' '),
     (No : 2; Str : 'konec'),
     (No : 3; Str : 'polozka'),
     (No : 4; Str : 'pridej'),
     (No : 5; Str : 'odeber'),
     (No : 6; Str : 'pocet'),
     (No : 7; Str : 'nazev'),
     (No : 8; Str : 'najdi'));
  cmNone =       0;
  cmError =      1;
  cmExit =       2;
  cmItem =       3;
  cmInc =        4;
  cmDec =        5;
  cmGetCount =   6;
  cmFindByID =   7;
  cmFindByName = 8;
  errDontSpeak =      0;
  errFatal =          1;
  errCorruptedStore = 2;
  errWrongParams =    3;
  errItemNotFound =   4;
  errTooManyItems =   5;
  errTooLittlePcs =   6;
  msgDontSpeak =  0;
  msgPcsInStore = 1;
  msgNameFound =  2;
  msgIDFound =    3;
  Msgs : Array[MessageCount] Of String =
    ('',
     'na sklade je kusu: ',
     'nazev polozky je: ',
     'byla nalezena polozka: ');
  Errs : Array[ErrorCount] Of String =
    ('CHYBA',
     'fakt divna chyba',
     'soubor se skladem neni platny nebo neexistuje',
     'spatny pocet parametru',
     'polozka neexistuje',
     'prilis mnoho polozek',
     'uz neni na sklade');
Var
  LocalStore : StoreType;
  DiskStore : File;
  InputCmd : CommandCount;
  InputParam1, InputParam2 : String;
  InputParamCount : LongInt;
  RawInput : String;
  Temp, TempPos : LongInt;
  TempA : String;

Procedure DebugMessage (msg : String);
Begin
{$ifdef sDebug}
  TextColor(DarkGray);
  WriteLn('Debug message: ', msg);
  TextColor(LightGray);
{$endif}
End;

Procedure OutputMessage (msg : String; msgtype : MessageCount);
Begin
{$ifdef sDontSpeak}
  WriteLn(Msgs[msgDontSpeak], msg);
{$else}
  WriteLn(Msgs[msgtype], msg);
{$endif}
End;

Procedure ErrorMessage (errtype : ErrorCount);
Begin
{$ifdef sDontSpeak}
  WriteLn(Errs[errDontSpeak]);
{$else}
  WriteLn(Errs[errtype]);
{$endif}
End;

Function StrFunc (val : Integer) : String;
Begin
  Str(val, Result);
End;

Function TrimString (inp, chr : String) : String;
Begin
  While inp[1]=chr Do inp:= Copy(inp, 2, Length(inp) -1);
  While inp[ Length(inp) ]=chr Do inp:= Copy(inp, 1, Length(inp) -1);
  Result:=inp;
End;

Function ParseString (inp, chr : String; Var outp1, outp2 : String) : LongInt;
Begin
  Result:= Pos(chr, TrimString(inp, chr) );
  If (Result<>0) Then Begin
    outp1:= Copy( TrimString(inp, chr) , 1, Result-1);
    outp2:= Copy( TrimString(inp, chr) , Result+1, Length(inp) -Result);
  End;
End;

Function PointToItem (xid: IDType) : PItemType;
Var
  Temp1 : LongInt;
Begin
  Result:=Nil;
  Temp1:= Low(LocalStore);
  While ( (Temp1<= High(LocalStore) ) And (LocalStore[Temp1].ID<>xid)) Do Temp1:=Temp1+1;
  If (Temp1<= High(LocalStore) ) Then Result:=@LocalStore[Temp1];
End;

Procedure ItemCommand (xid : IDType; xname : NameType);
Var
  PItem : PItemType;
Begin
  PItem:= PointToItem(xid);
  If (PItem<>Nil) Then
    If (xname='') Then
    Begin
      PItem^.ID:='';
      DebugMessage('Mazu polozku '''+xid+'''.');
    End Else
    Begin
      DebugMessage('Menim jmeno polozky '''+xid+''' na '''+xname+'''.');
      PItem^.Name:=xname;
    End Else
    Begin
      PItem:= PointToItem('');
      If (PItem<>Nil) Then
      Begin
        DebugMessage('Zakladam novou polozku '''+xid+''' s nazvem '''+xname+''' v poctu 0.');
        With PItem^ Do
          Begin
            Name:=xname;
            ID:=xid;
            Count:=0;
          End;
      End Else ErrorMessage(errTooManyItems);
    End;
End;

Function GetItemCount (xid : IDType) : CountType;
Var
  PItem : PItemType;
Begin
  PItem:= PointToItem(xid);
  If (PItem<>Nil) Then Result:=PItem^.Count Else Result:=-1;
End;

Function IncreaseItemCount (xid : IDType; xcount : CountType) : CountType;
Var
  PItem : PItemType;
Begin
  DebugMessage('Pridavam k polozce '''+xid+''' pocet '+ StrFunc(xcount) +'.');
  PItem:= PointToItem(xid);
  If (PItem<>Nil) Then
  Begin
    PItem^.Count:=PItem^.Count+xcount;
    Result:= GetItemCount(xid);
  End Else Result:=-1;
End;

Function GetName (xid : IDType) : NameType;
Var
  PItem : PItemType;
Begin
  DebugMessage('Ziskavam nazev podle ID: '''+xid+'''.');
  PItem:= PointToItem(xid);
  If (PItem<>Nil) Then Result:=PItem^.Name Else Result:='';
End;

Function FindByName (xname : NameType) : IDType;
Var
  Temp1 : LongInt;
Begin
  DebugMessage('Zkousim vyhledat podle nazvu: '''+xname+'''.');
  If (xname='') Then For Temp1:= Low(LocalStore) To High(LocalStore) Do
    Begin
      If (LocalStore[Temp1].Name<>'') Then OutputMessage(LocalStore[Temp1].ID , 3);
    End Else For Temp1:= Low(LocalStore) To High(LocalStore) Do
    Begin
      If ( Pos(xname, LocalStore[Temp1].Name)<>0) Then OutputMessage(LocalStore[Temp1].ID , 3);
    End;
End;

Procedure Initialize ();
Begin
  Assign(DiskStore, 'store.bin');
  If ( FileExists('store.bin') ) Then
  Begin
    Reset(DiskStore, 1);
    If ( FileSize(DiskStore) = SizeOf(LocalStore) ) Then
      BlockRead(DiskStore, LocalStore, SizeOf(LocalStore) ) Else
    Begin
      Close(DiskStore);
      ErrorMessage(errCorruptedStore);
      ReWrite(DiskStore, 1);
    End;
    Close(DiskStore);
  End Else
  Begin
    ErrorMessage(errCorruptedStore);
    ReWrite(DiskStore, 1);
    Close(DiskStore);
  End;
  DebugMessage('Inicializace dokoncena.');
End;

Procedure ExitProcedure ();
Begin
  ReWrite(DiskStore, 1);
  BlockWrite(DiskStore, LocalStore, SizeOf(LocalStore) );
  Close(DiskStore);
  DebugMessage('Uspesny konec programu.');
End;

Begin
  Initialize();
  ExitProc:=@ExitProcedure;
  While ( EoF(Input) =False) Do
  Begin
    InputCmd:=0;
    InputParam1:='';
    InputParam2:='';
    TempA:='';
    Temp:=0;
    InputParamCount:=3;

    ReadLn(RawInput);
    RawInput:= TrimString(RawInput, ' ');
    If ( ParseString(RawInput, ' ', RawInput, InputParam1) =0) Then InputParamCount:=InputParamCount-3 Else
      If ( ParseString(InputParam1, ' ', InputParam1, InputParam2) =0) Then InputParamCount:=InputParamCount-2 Else
        If ( ParseString(InputParam2, ' ', InputParam2, TempA) =0) Then InputParamCount:=InputParamCount-1;
    Case InputParamCount Of
      0 : DebugMessage('Prikaz je bez parametru.');
      1 : DebugMessage('Prikaz ma jeden parametr');
      2 : DebugMessage('Prikaz ma dva parametry.');
      3 : DebugMessage('Prikaz ma vice nez dva parametry');
    End;
    InputParam1:= TrimString(InputParam1, ' ');
    InputParam2:= TrimString(InputParam2, ' ');
    TempA:= TrimString(TempA, ' ');

    For Temp:= Low(CommandCount) To High(CommandCount) Do
      If ( LowerCase(RawInput) =Cms[Temp].Str) Then InputCmd:=Temp;
    DebugMessage('Prikaz byl vyhodnocen jako: '+ StrFunc(InputCmd) +' s parametry '''+InputParam1+''' a '''+InputParam2+''' a '''+TempA+'''.');

    Case InputCmd Of
      cmNone :
      Begin
        DebugMessage('Nic se nestalo.');
      End;

      cmError :
      Begin
        ErrorMessage(errFatal);
      End;

      cmExit :
      Begin
        DebugMessage('Regulerne koncim.');
        Exit;
      End;

      cmItem :
      Begin
        If ((InputParamCount=1) Or (InputParamCount=2)) Then
        Begin
          ItemCommand(InputParam1, InputParam2);
        End Else ErrorMessage(errWrongParams);
      End;

      cmInc :
      Begin
        If (InputParamCount=1) Then
        Begin
          If ( IncreaseItemCount(InputParam1, 1) <0) Then ErrorMessage(errItemNotFound);
        End Else ErrorMessage(errWrongParams);
      End;

      cmDec :
      Begin
        If (InputParamCount=1) Then
        Begin
          If ( GetItemCount(InputParam1) >0) Then
          Begin
            If ( IncreaseItemCount(InputParam1, -1) <0) Then ErrorMessage(errItemNotFound);
          End Else ErrorMessage(errTooLittlePcs);
        End Else ErrorMessage(errWrongParams);
      End;

      cmGetCount :
      Begin
        If (InputParamCount=1) Then
        Begin
          If ( GetItemCount(InputParam1) <0) Then
            ErrorMessage(errItemNotFound) Else
            OutputMessage( StrFunc( GetItemCount(InputParam1) ) , msgPcsInStore);
        End Else ErrorMessage(errWrongParams);
      End;

      cmFindByID :
      Begin
        If (InputParamCount=1) Then
        Begin
          If ( GetName(InputParam1) ='') Then ErrorMessage(errItemNotFound) Else
            OutputMessage( GetName(InputParam1) , msgNameFound);
        End Else ErrorMessage(errWrongParams);
      End;

      cmFindByName :
      Begin
        If ((InputParamCount=0) Or (InputParamCount=1)) Then
          Begin
            FindByName(InputParam1)
          End Else ErrorMessage(errWrongParams);

      End;
    End;
  End;
End.

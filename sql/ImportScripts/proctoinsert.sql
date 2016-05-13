
DELIMITER //
 
CREATE PROCEDURE tbimp ()
BEGIN
    DECLARE tmptitle TEXT;
    DECLARE tmpdesc TEXT;
    DECLARE tmptag TEXT;
    DECLARE cur CURSOR FOR select * from tmpimport;
    
    OPEN cur;
    
    testLoop: LOOP
		FETCH cur INTO tmptitle, tmpdesc, tmptag;
        CALL ProcInsertQuestion(tmptitle, tmpdesc, tmptag, 100);
    END LOOP testLoop;
    
END//

DROP PROCEDURE tbimp;

CALL tbimp();


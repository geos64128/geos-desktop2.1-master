
void mnu_geos_geosInfo (void)
{
    GotoFirstMenu();
    DlgBoxOk("GEOS Kernal designed by:", "Copyright 1986, 1988, Berkeley Softworks");
};

void mnu_geos_desktopInfo (void)
{
    GotoFirstMenu();
    DlgBoxOk("DESKTOP v2.1", "Written By Scott Hutter - 2020");
};

void mnu_geos_selectPrinter (void)
{
    GotoFirstMenu();
};

void mnu_geos_selectInput (void)
{
    GotoFirstMenu();
};

void mnu_file_open (void)
{
    unsigned char tmp;

    GotoFirstMenu();

    if(numSelected > 1)
    {
        DlgBoxOk("No multiple file operation for", "this feature.");
    }
    else
    {
        for(tmp=0; tmp<8;tmp++)
        {
            if(padIcons[tmp].selected == 1)
            {
                iconHandlerRunApp(tmp);
                break;
            }
        }
    }
};

void mnu_file_duplicate (void)
{
    GotoFirstMenu();
};

void mnu_file_rename (void)
{
    GotoFirstMenu();
};

void mnu_file_info (void)
{
    unsigned char tmp;

    GotoFirstMenu();

    if(numSelected > 1)
    {
        DlgBoxOk("No multiple file operation for", "this feature.");
    }
    else
    {
        for(tmp=0; tmp<8;tmp++)
        {
            if(padIcons[tmp].selected == 1)
            {
                info_draw(padIcons[tmp].filename);
                break;
            }
        }
    }
};

void mnu_file_print (void)
{
    GotoFirstMenu();
};

void mnu_file_delete (void)
{
    GotoFirstMenu();
};

void mnu_file_undodelete (void)
{
    GotoFirstMenu();
};

void mnu_view_byicon (void)
{
    GotoFirstMenu();
};

void mnu_view_bysize (void)
{
    GotoFirstMenu();
};

void mnu_view_bytype (void)
{
    GotoFirstMenu();
};

void mnu_view_bydate (void)
{
    GotoFirstMenu();
};

void mnu_view_byname (void)
{
    GotoFirstMenu();
};

void mnu_disk_open (void)
{
    GotoFirstMenu();
};

void mnu_disk_close (void)
{
    GotoFirstMenu();
};

void mnu_disk_rename (void)
{
    GotoFirstMenu();
};

void mnu_disk_copy (void)
{
    GotoFirstMenu();
};

void mnu_disk_validate (void)
{
    GotoFirstMenu();
};

void mnu_disk_erase (void)
{
    GotoFirstMenu();
};

void mnu_disk_format (void)
{
    GotoFirstMenu();
};

void mnu_select_allpages (void)
{
    GotoFirstMenu();
};

void mnu_select_pagefiles (void)
{
    GotoFirstMenu();

    selectAllFileIcons();
};

void mnu_select_borderfiles (void)
{
    GotoFirstMenu();
};

void mnu_page_append (void)
{
    GotoFirstMenu();
};

void mnu_page_delete (void)
{
    GotoFirstMenu();
};

void mnu_options_setclock (void)
{
    GotoFirstMenu();
};

void mnu_options_reset (void)
{
    GotoFirstMenu();
    changeDevice(PEEK(0x8489));
    
};

void mnu_options_basic (void)
{
    remove_hook();
    ToBASIC();
};

void mnu_options_shortcuts (void)
{
    GotoFirstMenu();
};
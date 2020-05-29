# -*- coding: utf-8 -*-
import ROOT as r
from ROOT import gStyle, gROOT
from copy import deepcopy
import sys
from markers import markerColors, markerTypes, markerColorsMerge
r.gROOT.SetBatch(True)
import math


############################################# CHANGE IF NECESSARY ###########################################################

#############################################################################################################################

def makePlotReturn(path, files, plotscaffold, merge, normalize):
    if not merge :
      res = files
      #res = r.TFile.Open(path + files)
      resplot = res.Get(plotscaffold)
    else :
      done = False
      for fil in files :
        otherPlot = fil.Get(plotscaffold)
        #print plotscaffold
        #otherPlot.SetTitle("")
       # if otherPlot.Integral()<=0 : continue
        makeNonNegativeHistos(otherPlot)

        if not done: 
          done = True
          resplot = otherPlot.Clone()
        else : resplot.Add(otherPlot)
        
        del otherPlot

    if normalize==1 and resplot.Integral() > 0 : resplot.Scale (1. / resplot.Integral() )
    elif normalize>1 : resplot.Scale (normalize)


    return resplot

def makePlot(hlist, path, files, plotscaffold, merge, normalize):
    
    if not merge :
      res = r.TFile.Open(path + files)
      resplot = res.Get(plotscaffold)
    else :
      #res = r.TFile.Open(path+files[0]+'.root')
      res = files[0]
      resplot = res.Get(plotscaffold)
      makeNonNegativeHistos(resplot)
      for i in range (1,len(files)) :
        otherFile = files[i]
        #otherFile = r.TFile.Open(path+files[i]+'.root')
        otherPlot = otherFile.Get(plotscaffold)
        makeNonNegativeHistos(otherPlot)
        
        resplot.Add(otherPlot)
        #otherFile.Close();
        del otherPlot

    if normalize==1 and resplot.Integral() > 0 : resplot.Scale (1. / resplot.Integral() )
    elif normalize>1 : resplot.Scale (normalize)


    hlist.append(deepcopy(resplot))
    if merge : del resplot
    if not merge : res.Close(); del res, resplot
    #res.Close(); del res, resplot
    return

def combinePlots (hlist, legends, plottingStuff, path, savescaffold, logy=False, normalize=False): 
    print "Combining list of plots"
    if len(hlist) == 0: raise RuntimeError("Empty list of plots")
    c = r.TCanvas("c", "c", 800, 800)

    binWidth = hlist[0].GetBinWidth(1)
    lowerEdge = hlist[0].GetBinCenter(1) - binWidth / 2
    upperEdge = hlist[0].GetBinCenter(hlist[0].GetNbinsX()) + binWidth / 2
   
    maximum = 0

    gStyle.SetOptStat(0)
    gStyle.SetTitleFontSize(.05);
    gStyle.SetLabelSize(.03, "XY");

    leg = r.TLegend(plottingStuff['legxlow'], plottingStuff['legylow'], plottingStuff['legxhigh'], plottingStuff['legyhigh'])
    for iplot in range(len(hlist)):
        if hlist[iplot].Integral() > 0 :  hlist[iplot].Scale(1./ hlist[iplot].Integral())
        if hlist[iplot].GetMaximum() > maximum: 
          maximum = hlist[iplot].GetMaximum()
        if legends[iplot] in markerColorsMerge : 
          #hlist[iplot].SetFillColor(markerColorsMerge[legends[iplot]])
          hlist[iplot].SetMarkerColor(markerColorsMerge[legends[iplot]])
          hlist[iplot].SetLineColor(markerColorsMerge[legends[iplot]])
        else: 
          #hlist[iplot].SetFillColor(markerColors[iplot % len(markerColors)])
          hlist[iplot].SetMarkerColor(markerColors[iplot % len(markerColors)])
          hlist[iplot].SetLineColor(markerColors[iplot % len(markerColors)])
        
        #if legends[iplot]=="VBFHHSM" or legends[iplot]=="GGHHSM" : hlist[iplot].SetLineStyle(r.kDashed) 
        
        hlist[iplot].SetMarkerStyle(20)
        leg.AddEntry(hlist[iplot], legends[iplot], "PL")

    dummy_hist = r.TH1F("dummy", " ;" + hlist[0].GetXaxis().GetTitle() + "; Normalized entries / {:.2f}".format(binWidth), hlist[0].GetNbinsX(), lowerEdge, upperEdge)
    dummy_hist.GetYaxis().SetRangeUser(0, 1.35 * maximum) if not logy else dummy_hist.GetYaxis().SetRangeUser(1E-3, 100 * maximum)
    # if logy: dummy_hist.SetMinimum(1E-3)
    dummy_hist.GetYaxis().SetTitleOffset(1.4)
    dummy_hist.Draw()
   
    for iplot in range(len(hlist)):
        hlist[iplot].Draw("histosame")
    
    leg.SetFillColor(4001)
    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.Draw()
   
    r.gPad.Update()
    #hlist[0].GetYaxis().SetRangeUser(plottingStuff['lowlimityaxis'], plottingStuff['highlimityaxis'])
    
    firstLabel = "#scale[1.5]{CMS} private work"
    otherStuff = ["channel", "selection", "region"]
    for elem in otherStuff:
        if elem in plottingStuff.keys():
            firstLabel += "," + (elem != "#tau#tau") * " "
            firstLabel += plottingStuff[elem]

    firsttex = r.TLatex()
    firsttex.SetTextSize(0.03)
    firsttex.DrawLatexNDC(0.11,0.91,firstLabel)
    firsttex.Draw("same");

    secondtext = r.TLatex()
    toDisplay = r.TString()
    toDisplay  = r.TString("41.6 fb^{-1} 13 TeV")
    secondtext.SetTextSize(0.035)
    secondtext.SetTextAlign(31)
    secondtext.DrawLatexNDC(0.90, 0.91, toDisplay.Data())
    secondtext.Draw("same")

    r.gPad.SetTicks(1,1);
    r.gPad.RedrawAxis();

    if logy: c.SetLogy()

    if not logy : c.SaveAs(path + savescaffold + ".png")
    else : c.SaveAs(path + savescaffold + "_logy.png")
    if not logy : c.SaveAs(path + savescaffold + ".pdf")
    else : c.SaveAs(path + savescaffold + "_logy.pdf")
    #if not logy : c.SaveAs(path + savescaffold + ".root")
    #else c.SaveAs(path + savescaffold + "_logy.root")
    
    c.Close(); del c



def dataMCPlots (dataPlot, MClist, signalList, MClegends, plottingStuff, path, savescaffold, logy=False): 
    print "Combining list of plots"
    if len(MClist) == 0 or len(dataPlot) == 0: raise RuntimeError("Empty list of plots")
    #c   = r.TCanvas("c", "c", 800, 800)
    c   = r.TCanvas("c","c",10,10,1000,1000);
    #c.Divide(1,2,0,0)
    pad1 = r.TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,31);
    pad2 = r.TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,32);

    pad1.SetFillColor(r.kWhite);
    pad2.SetFillColor(r.kWhite);
    pad1.Draw();
    pad2.Draw("same");
    pad1.cd();
    pad1.SetBottomMargin(0.1);
    #pad1.SetLeftMargin(0.2);

    maxim = -1; 

    gStyle.SetOptStat(0)
    leg = r.TLegend(plottingStuff['legxlow'], plottingStuff['legylow'], plottingStuff['legxhigh'], plottingStuff['legyhigh'])
    
    hs = r.THStack("hs","")
    nEntries = 0
    for iplot in range(len(MClist)):
      if MClegends[iplot] in markerColorsMerge : MClist[iplot].SetFillColor(markerColorsMerge[MClegends[iplot]])
      else: MClist[iplot].SetFillColor(markerColors[iplot % len(markerColors)])
      nEntries += MClist[iplot].Integral()
      leg.AddEntry(MClist[iplot], MClegends[iplot], "f")

    dataPlot[0].SetMarkerColor(r.kBlack)
    dataPlot[0].SetMarkerSize(1)
    dataPlot[0].SetMarkerStyle(20)
    dataPlot[0].SetLineColor(r.kBlack)
    binWidth = dataPlot[0].GetBinWidth(1)
    lowerEdge = dataPlot[0].GetBinCenter(1) - binWidth / 2
    upperEdge = dataPlot[0].GetBinCenter(dataPlot[0].GetNbinsX()) + binWidth / 2
    
    maximum = dataPlot[0].GetMaximum()
    for iplot in range(len(MClist)):
      if MClist[iplot].GetMaximum() > maximum: maximum = MClist[iplot].GetMaximum()
      if iplot == 0 : h = MClist[iplot].Clone()
      else : h.Add(MClist[iplot])
      hs.Add(MClist[iplot])

    firstLabel = "#scale[1.5]{CMS} private work"
    otherStuff = ["channel", "selection", "region"]
    for elem in otherStuff:
        if elem in plottingStuff.keys():
            firstLabel += ", " 
            firstLabel += plottingStuff[elem]

    preliminary = r.TLatex(0.11,0.91,firstLabel);

    preliminary.SetTextSize(0.03)
    preliminary.SetNDC();
    secondtext = r.TLatex()
    toDisplay = r.TString()
    secondtext = r.TLatex(0.76, 0.91, "41.6 fb^{-1}, 13 TeV")
    secondtext.SetTextSize(0.03)
    secondtext.SetNDC()
    #preliminary.SetTextFont(42);

    #c.Divide(1,2,0,0);
    pad1.cd();

    unit = ""
    if "(" in dataPlot[0].GetXaxis().GetTitle() and ")" in dataPlot[0].GetXaxis().GetTitle():
        left = dataPlot[0].GetXaxis().GetTitle().index("(")+1
        right = dataPlot[0].GetXaxis().GetTitle().index(")")
        unit = dataPlot[0].GetXaxis().GetTitle()[left:right]

    dummy_hist = r.TH1F("dummy", " ;" + dataPlot[0].GetXaxis().GetTitle() + "; Entries / {:.2f} {}".format(binWidth, unit), dataPlot[0].GetNbinsX(), lowerEdge, upperEdge)
    dummy_hist.GetYaxis().SetRangeUser(0, 1.35*maximum)
    dummy_hist.Draw()
    #c.GetPad(1).SetBottomMargin(0.1)
    hs.Draw("histo, same")
    dataPlot[0].Draw("P, same")
    
    for iplot in range(len(signalList)):
      if MClegends[iplot+len(MClist)] in markerColorsMerge : 
          signalList[iplot].SetLineColor(markerColorsMerge[MClegends[len(MClist)+iplot]])
      else: 
        print "Better add a color to the sample " +  MClegends[iplot+len(MClist)] + " and restart"
        sys.exit()
      #if signalList[iplot].Integral()!=0 and dataPlot[0].Integral()!=0 :  signalList[iplot].Scale(dataPlot[0].Integral()/(signalList[iplot].Integral()))
     
      #NORMALISING
      if "GGHHSM" in MClegends[iplot+len(MClist)] :  
        signalList[iplot].Scale(10)          
        MClegends[iplot+len(MClist)] += " (10pb^{-1})"
      elif "VBFHHSM" in MClegends[iplot+len(MClist)] :
        signalList[iplot].Scale(10)
        MClegends[iplot+len(MClist)] += " (10pb^{-1})"
      
      signalList[iplot].SetLineWidth(2)
      signalList[iplot].Draw("hist same")
      leg.AddEntry(signalList[iplot], MClegends[len(MClist)+iplot], "L")
    




    leg.AddEntry(dataPlot[0], "data", "PL")
    leg.SetFillColor(4001)
    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.Draw("same")
    preliminary.Draw();
    secondtext.Draw("")

    r.gPad.SetTicks(1,1);
    r.gPad.RedrawAxis();

    hD = dataPlot[0].Clone()
    hD.Divide(h)
    hD.GetYaxis().SetRangeUser(0.5,1.5)
    hD.GetYaxis().SetNdivisions(4)
    hD.GetYaxis().SetTitleOffset(0.45);
    hD.SetLabelSize(0.08, "xy");
    hD.SetTitleSize(0.08, "xy");
    pad2.cd(); 
    pad2.SetGrid()
    hD.SetTitle(" ; ; Data/Background")
    hD.Draw()

    
    

    #hlist[0].GetYaxis().SetRangeUser(plottingStuff['lowlimityaxis'], plottingStuff['highlimityaxis'])
    
    #firsttex = r.TLatex()
    #firsttex.SetTextSize(0.03)
    #firsttex.DrawLatexNDC(0.11,0.91,"#scale[1.5]{CMS} Preliminary")
    #firsttex.Draw("same");

    #secondtext = r.TLatex()
    #toDisplay = r.TString()
    #toDisplay  = r.TString("60.0 fb^{-1} 13 TeV")
    #secondtext.SetTextSize(0.035)
    #secondtext.SetTextAlign(31)
    #secondtext.DrawLatexNDC(0.90, 0.91, toDisplay.Data())
    #secondtext.Draw("same")


    if logy: c.SetLogy()

    if not logy : c.SaveAs(path + savescaffold + ".png")
    else : c.SaveAs(path + savescaffold + "_logy.png")
    if not logy : c.SaveAs(path + savescaffold + ".pdf")
    else : c.SaveAs(path + savescaffold + "_logy.pdf")
    #if not logy : c.SaveAs(path + savescaffold + ".root")
    #else c.SaveAs(path + savescaffold + "_logy.root")
    
    c.Close(); del c

def makeNonNegativeHistos (h):
   integral = h.Integral()
   sum_bin = 0
   for b in range (1, h.GetNbinsX()+1):
     if (h.GetBinContent(b) < 0):
       h.SetBinContent (b, 1E-4)
     sum_bin += h.GetBinContent(b)
   integralNew = h.Integral()        
 #  if (integralNew != integral):
 #    print "** INFO: removed neg bins from histo " , h.GetName(), integral, integralNew, sum_bin
   
   if math.isnan(sum_bin) :
     h.Scale(0)
 #    print "NaN obtained, scaled to 0", h.Integral()

   # print h.GetName() , integral , integralNew
   if integralNew == 0:
     h.Scale(0)
   else:
     h.Scale(integral/integralNew) 




